#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include <sys/mman.h>

enum Opcode { Sub,
	      Mul,
	      Push,
	      Store,
	      Load,
	      Bnez,
	      Halt };

class VM {
      public:
	using AotFunc = std::int64_t(void *);

	VM(std::initializer_list<std::int8_t> code) : code_(code) {}

	std::int64_t Run() {
		char stack[64 * 8];
		return Build()(stack);
	}

	AotFunc *Build() {
		std::unordered_map<int, std::size_t> labels;
		std::unordered_map<std::size_t, int> backfill;
		buffer_.clear();
		// generate prologue
		GenCode({
		    0x53,	      // push rbx
		    0x41, 0x54,	      // push r12
		    0x49, 0x89, 0xfc, // mov  r12, rdi
		});
		// generate code
		for (int pc = 0; pc < code_.size(); ++pc) {
			labels[pc] = buffer_.size();
			switch (code_[pc]) {
			case Sub: {
				GenCode({
				    0x49, 0x8b, 0x04, 0x24, // mov  rax, qword ptr [r12]
				    0x49, 0x83, 0xec, 0x08, // sub  r12, 8
				    0x49, 0x29, 0x04, 0x24, // sub  qword ptr [r12], rax
				});
				break;
			}
			case Mul: {
				GenCode({
				    0x49, 0x8b, 0x04, 0x24,	  // mov  rax, qword ptr [r12]
				    0x49, 0x83, 0xec, 0x08,	  // sub  r12, 8
				    0x49, 0x0f, 0xaf, 0x04, 0x24, // imul rax, qword ptr [r12]
				    0x49, 0x89, 0x04, 0x24,	  // mov  qword ptr [r12], rax
				});
				break;
			}
			case Push: {
				std::int64_t imm = code_[++pc];
				GenCode({
				    0x48, 0xb8, // mov  rax, imm
				});
				for (int i = 0; i < 8; ++i) {
					buffer_.push_back(reinterpret_cast<std::uint8_t *>(&imm)[i]);
				}
				GenCode({
				    0x49, 0x83, 0xc4, 0x08, // add  r12, 8
				    0x49, 0x89, 0x04, 0x24, // mov  qword ptr [r12], rax
				});
				break;
			}
			case Store: {
				GenCode({
				    0x49, 0x8b, 0x1c, 0x24, // mov  rbx, qword ptr [r12]
				    0x49, 0x83, 0xec, 0x08, // sub  r12, 8
				});
				break;
			}
			case Load: {
				GenCode({
				    0x49, 0x83, 0xc4, 0x08, // add  r12, 8
				    0x49, 0x89, 0x1c, 0x24, // mov  qword ptr [r12], rbx
				});
				break;
			}
			case Bnez: {
				GenCode({
				    0x49, 0x8b, 0x04, 0x24, // mov  rax, qword ptr [r12]
				    0x49, 0x83, 0xec, 0x08, // sub  r12, 8
				    0x48, 0x83, 0xf8, 0x00, // cmp  rax, 0
				    0x0f, 0x85,		    // jnz  label
				});
				backfill[buffer_.size()] = pc + code_[pc + 1];
				buffer_.resize(buffer_.size() + 4);
				++pc;
				break;
			}
			case Halt: {
				GenCode({
				    0x49, 0x8b, 0x04, 0x24, // mov  rax, qword ptr [r12]
				    0x41, 0x5c,		    // pop  r12
				    0x5b,		    // pop  rbx
				    0xc3,		    // ret
				});
				break;
			}
			}
		}
		// backfill labels
		for (const auto &it : backfill) {
			std::int32_t offset = labels[it.second];
			offset -= it.first + 4;
			for (int i = 0; i < 4; ++i) {
				buffer_[it.first + i] = reinterpret_cast<std::uint8_t *>(&offset)[i];
			}
		}
		// create executable buffer
		auto buf_size = buffer_.size();
		auto buf = mmap(nullptr, buf_size, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		memcpy(buf, buffer_.data(), buf_size);
		mprotect(buf, buf_size, PROT_READ | PROT_EXEC);
		exe_buf_ = ExeBufPtr(buf, [buf_size](void *buf) { munmap(buf, buf_size); });
		return reinterpret_cast<AotFunc *>(buf);
	}

      private:
	using ExeBufPtr = std::unique_ptr<void, std::function<void(void *)>>;

	void GenCode(std::initializer_list<std::uint8_t> code) {
		buffer_.insert(buffer_.end(), code);
	}

	std::vector<std::int8_t> code_;
	std::vector<std::uint8_t> buffer_;
	ExeBufPtr exe_buf_;
};

int main(int argc, const char *argv[]) {
	VM vm = {
	    Push,
	    20,
	    Store,
	    Push,
	    1,
	    Load,
	    Mul,
	    Load,
	    Push,
	    1,
	    Sub,
	    Store,
	    Load,
	    Bnez,
	    -8,
	    Halt,
	};
	std::cout << vm.Run() << std::endl;
	return 0;
}