let totalTime = 10 * 60; // 10分钟
let timer = document.getElementById("timer");
let scoreDisplay = document.getElementById("scoreDisplay");
let scoreDiv = document.getElementById("score");

let correctAnswers = {
  q1: 'b',
  q2: 'a',
};

let interval;

function startTimer() {
  interval = setInterval(function() {
    if (totalTime <= 0) {
      clearInterval(interval);
      alert("考试时间结束，自动评分！");
      gradeExam();
    } else {
      totalTime--;
      let minutes = Math.floor(totalTime / 60);
      let seconds = totalTime % 60;
      timer.textContent = `剩余时间: ${minutes}:${seconds < 10 ? '0' : ''}${seconds}`;
    }
  }, 1000);
}

function gradeExam() {
  let form = document.getElementById("examForm");
  let totalScore = 0;
  
  // 检查每个问题的答案
  for (let question in correctAnswers) {
    let selected = form.querySelector(`input[name="${question}"]:checked`);
    if (selected && selected.value === correctAnswers[question]) {
      totalScore++;
    }
  }

  scoreDisplay.textContent = `得分：${totalScore} / 2`;
  scoreDiv.style.display = "block"; // 显示成绩
}

document.getElementById("examForm").addEventListener("submit", function (e) {
  e.preventDefault();
  gradeExam();
});

startTimer(); // 启动计时器
