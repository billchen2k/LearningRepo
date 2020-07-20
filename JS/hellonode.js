/**
 * 打招呼
 * @param {*} name 姓名
 * @return {string} 招呼语
 */
function sayHi(name) {
  return `Hello, ${name}!`;
}

tt = [10, 20, 25, 5, 1];
tt.sort((x, y) => x - y);
tt.forEach((one) => {
  console.log(Math.pow(one, 2));
});

console.log(sayHi('Bill Chen'));

ladder = {
  step: 0,
  up() {
    this.step++;
    return this;
  },
  down() {
    this.step--;
    return this;
  },
  showStep: function () { // 显示当前的 step
    console.log(this.step);
  }
};