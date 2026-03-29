function createInputs() {
    k = parseInt(document.getElementById("number").value);
    var inputs = document.getElementById("inputs");
    for (i=0; i<k; i++) {
        var inpt = document.createElement("input");
        inpt.value = i+1;
        inputs.appendChild(inpt);
    }
}

function calc() {
    var divInputs = document.getElementById("inputs");
    inputs = divInputs.getElementsByTagName('input');
    var sum = 0;
    console.log("Собранные поля input и их количество:", inputs, inputs.length);
    for (let item of inputs) {
        sum += parseInt(item.value);
    }
    var avg = sum/inputs.length;
    console.log("Средний балл", Math.round(avg * 100)/100);
    var rate = Math.round(avg);
    if (avg >= 0.00 && avg < 2.65) {
        var rate = 2;
    }
    else if (avg >= 2.65 && avg < 3.65) {
        var rate = 3;
    }
    else if (avg >= 3.65 && avg < 4.65) {
        var rate = 4;
    }
    else if (avg >= 4.65) {
        var rate = 5;
    }
    document.getElementById('result').innerHTML = Math.round(avg * 100)/100;
    document.getElementById('res').innerHTML = rate;
}