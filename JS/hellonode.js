/**
 * 打招呼
 * @param {*} name 姓名
 * @return {string} 招呼语
 */
function sayHi(name) {
  return `Hello, ${name}!`;
}

function sayGoodbye(name) {
  return `Goodbye, ${name}`;
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
    return this;
  }
};

const http = require('http');
const { clearTimeout } = require('timers');

const hostname = '127.0.0.1';
const port = 3000;

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  // res.setHeader('Content-Type', 'text/plain');
  res.end('<h1>Hello World</h1>');
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});

function summer(...args) {
  let sum = 0;
  for (let arg of args) sum += arg;
  return sum;
}



let sum = function(num) {
  let currentSum = num;

  function f(a) {
    currentSum += a;
    setTimeout(() => console.log('Time Out!'), 1000);
    return f;
  }

  f[Symbol.toPrimitive] = function () {
    return currentSum;
  }
  return f;
}

Timer = {
  tick: 0,
  timerId: 0,
  start() {
    Timer.timerId = setInterval(function() {
      Timer.tick++
      console.log(Timer.tick);
    }, 1000);
  },
  pause() {
    clearInterval(Timer.timerId);
  },
  reset() {
    Timer.pause();
    Timer.tick = 0;
  }
}

delete Timer
// var highestTimeoutId = setTimeout(() => null, 3000);
for (var i = 0; i <= 100000; i++) {
  clearInterval(i);
}

Timer.pause();

start = Date.now();
times = [];

setTimeout(function run() {
  times.push(Date.now() - start); // 保存前一个调用的延时

  if (start + 10000 < Date.now()) console.log(times); // 100 毫秒之后，显示延时信息
  else setTimeout(run); // 否则重新调度
});

function cachingDecorator(func) {
  let cache = new Map();

  return function (x) {
    if (cache.has(x)) {    // 如果缓存中有对应的结果
      return cache.get(x); // 从缓存中读取结果
    }

    let result = func(x);  // 否则就调用 func
    cache.set(x, result);  // 然后将结果缓存（记住）下来
    return result;
  };
}

function delay(f, ms) {
  return function () {
    setTimeout(() => f.apply(this, arguments), ms);
  };

}

function info(...args) {
  console.log(arguments)
}

let user = {
  get name() {
    return this._name;
  },

  set name(value) {
    if (value.length < 4) {
      console.log("Name is too short, need at least 4 characters");
      return;
    }
    this._name = value;
  }
};

new Promise((resolve, reject) => {
  setTimeout(() => {
    console.log("Fisrst finished.");
    resolve(0);
  }, 1000);
}).then(() => {
  setTimeout(() => {
    throw new Error('Hello, World.');
  }, 1000);
}).finally(() => console.log('Finally'))
  .catch(e => console.log(e));


Promise.all([
  new Promise(resolve => setTimeout(() => resolve(1), 3000)), // 1
  new Promise(resolve => setTimeout(() => resolve(2), 2000)), // 2
  new Promise(resolve => setTimeout(() => resolve(3), 1000))  // 3
]).then(console.log);


function promisify(f) {
  return function (...args) { // 返回一个包装函数（wrapper-function）
    return new Promise((resolve, reject) => {
      function callback(err, result) { // 我们对 f 的自定义的回调
        if (err) {
          reject(err);
        } else {
          resolve(result);
        }
      }

      args.push(callback); // 将我们的自定义的回调附加到 f 参数（arguments）的末尾

      f.call(this, ...args); // 调用原始的函数
    });
  };
};

// 用法：
let loadScriptPromise = promisify(loadScript);
loadScriptPromise(...).then(...);

async function atest(v) {
  let responce = await new Promise((resolve, reject) => {
    setTimeout(() => {
      console.log('function running');
      resolve(v);
    }, 1000);
  });
  return String(responce).repeat(10);
}

console.log('before call');
atest('Bill').then(
  (data) => {
    console.log(`Data get: ${data}`);
  }
)
console.log('after call');

function loadJson(url) {
  return fetch(url)
    .then(response => {
      if (response.status == 200) {
        return response.json();
      } else {
        throw new Error(response.status);
      }
    })
}

async function loadJson(url) {
  let response = await fetch(url);
  if (response.status == 200) {
    return response;
  }
  else {
    throw new Error(response.status);
  }
}





async function autoFixTest(str) {
  try {
    const data = await new Promise((resolve, reject) => {
      setTimeout(() => {
        resolve(str);
      }, 1000);
    });
    console.log((String(data) + '\n').repeat(10));
    return data;
  }
  catch (e) {
    console.log(e.message);
  }
}

autoFixTest(100);

loadJson('no-such-user.json').catch(alert); // Error: 404


function add(n) {
  let sum = n;
  function _(n) {
    sum += n;
    return _;
  }
  _[Symbol.toPrimitive] = () => sum;
  return _;
}

let filtered = [1, 3, 5, 7, 9]
filtered = filtered.map(one => one * one)