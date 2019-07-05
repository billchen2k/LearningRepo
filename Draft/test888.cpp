#include <iostream>

class father{
    private:
      int age = 40;
      
    protected:
      int height = 180;

    public:
      int getAge() {
	      return age;
	}
};

class son: public father{

};

class grandson: public son{
    public:
    int getHeight(){
	    return height;
    }
};

int main() {
	grandson SON;
	std::cout << SON.getHeight() << std::endl;
}