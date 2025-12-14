async function asy1() {
    console.log(1);
    await asy2();
    console.log(2);
}
async function asy2() {
    await setTimeout(() => {
        Promise.resolve().then(() => {
            console.log(3);
        });
        console.log(4);
    }, 0);
}

const say3 = async () => {
    Promise.resolve().then(() => {
        console.log(5);
    });
};
asy1();
console.log(6);
say3();