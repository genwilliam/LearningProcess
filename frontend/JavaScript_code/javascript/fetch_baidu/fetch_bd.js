import { get } from "https";

function fetchBaidu() {
  return new Promise((resolve, reject) => {
    const options = {
      hostname: "www.baidu.com",
      port: 443,
      path: "/",
      method: "GET",
      rejectUnauthorized: false, // ⚠️ 忽略 SSL 验证
    };

    get(options, (res) => {
      let data = "";
      res.on("data", (chunk) => {
        data += chunk;
      });
      res.on("end", () => resolve(data));
    }).on("error", (err) => reject(err));
  });
}

fetchBaidu()
  .then((html) => {
    console.log("类型:", typeof html); // string
    console.log("前200字符:\n", html.slice(0, 200));
  })
  .catch((err) => console.error("请求失败:", err));
