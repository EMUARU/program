var money = 10000;
var selectedmoney = 0;
var numbers = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36];
var colors = [];
var startAngle = 0;
var arc = Math.PI / 180 * 360 / 37;
var spinTimeout = null;

var spinArcStart = 10;
var spinTime = 0;
var spinTimeTotal = 0;
var counts = 0;
var moneycounts = 0;
var kidney = 2;
var tdnames = [];
var tdmoney = [];
var ctx;

function draw() {
	randomnum();
	drawRouletteWheel();
}

function randomnum() {
	for (var i = 0; i < 37; i++) {
		var num1 = Math.floor(Math.random() * 37), num2 = Math.floor(Math.random() * 37);
		if (num1 != 0 && num2 != 0) {
			var temp = numbers[num1];
			numbers[num1] = numbers[num2];
			numbers[num2] = temp;
		}
	}
}

function drawRouletteWheel() {
	var canvas = document.getElementById("wheelcanvas");
	if (canvas.getContext) {
		var outsideRadius = 236;
		var textRadius = 200;
		var insideRadius = 175;

		ctx = canvas.getContext("2d");
		ctx.clearRect(0, 0, 500, 500);


		ctx.strokeStyle = "#FFD700";
		ctx.lineWidth = 5;

		ctx.font = 'bold 12px sans-serif';

		for (var i = 0; i < 37; i++) {
			var angle = startAngle + i * arc;
			if (numbers[i] == 0) {
				ctx.fillStyle = "#00FF00";
				colors[i] = "green";
				document.getElementById("td_one_0_").style.background = "#00FF00";
			} else if (i % 2 == 0) {
				ctx.fillStyle = "#FF0000";
				colors[i] = "red";
				document.getElementById("td_one_" + numbers[i] + "_").style.background = "#FF0000";
			} else {
				ctx.fillStyle = "#000000";
				colors[i] = "black";
				document.getElementById("td_one_" + numbers[i] + "_").style.background = "#000000";
			}

			ctx.beginPath();
			ctx.arc(250, 250, outsideRadius, angle, angle + arc, false);
			ctx.arc(250, 250, insideRadius, angle + arc, angle, true);
			ctx.fill();
			ctx.stroke();

			ctx.save();
			ctx.font = "20px Georgia";
			ctx.shadowOffsetX = -1;
			ctx.shadowOffsetY = -1;
			ctx.shadowBlur = 0;
			ctx.shadowColor = "#DDDDDD";
			ctx.fillStyle = "#FFFFFF";
			ctx.translate(250 + Math.cos(angle + arc / 2) * textRadius, 250 + Math.sin(angle + arc / 2) * textRadius);
			ctx.rotate(angle + arc / 2 + Math.PI / 2);
			var text = numbers[i];
			ctx.fillText(text, -ctx.measureText(text).width / 2, 0);
			ctx.restore();
		}

		//Arrow
		ctx.fillStyle = "#00BBFF";
		ctx.beginPath();
		ctx.moveTo(250 - 7, 250 - (outsideRadius + 5));
		ctx.lineTo(250 + 7, 250 - (outsideRadius + 5));
		ctx.lineTo(250 + 0, 250 - (outsideRadius - 18));
		ctx.lineTo(250 - 7, 250 - (outsideRadius + 5));
		ctx.fill();
	}
}

function spin() {
	spinAngleStart = Math.random() * 10 + 10;
	spinTime = 0;
	spinTimeTotal = Math.random() * 3 + 10 * 1000;
	rotateWheel();
}

function rotateWheel() {
	spinTime += 50;
	if (spinTime >= spinTimeTotal) {
		stopRotateWheel();
		return;
	}
	var spinAngle = spinAngleStart - easeOut(spinTime, 0, spinAngleStart, spinTimeTotal);
	startAngle += (spinAngle * Math.PI / 180);
	drawRouletteWheel();
	spinTimeout = setTimeout('rotateWheel()', 15);
}

function stopRotateWheel() {
	clearTimeout(spinTimeout);
	var degrees = startAngle * 180 / Math.PI + 90;
	var arcd = arc * 180 / Math.PI;
	var index = Math.floor((360 - degrees % 360) / arcd);
	ctx.save();
	ctx.font = 'bold 150px sans-serif';
	var text = numbers[index];
	ctx.fillText(text, 250 - ctx.measureText(text).width / 2, 250 + 50);
	ctx.restore();
	openaward(numbers[index], index);
}

function easeOut(t, b, c, d) {
	var ts = (t /= d) * t;
	var tc = ts * t;
	return b + c * (tc + -3 * ts + 3 * t);
}

function maketable() {
	var tb = document.getElementById("tb");
	{
		var line = document.createElement("tr");
		buildtd("", "white", "white", "tdnull", "flattd", "3", "1", line, "clicktd(this,event)");
		for (var i = 1; i <= 34; i += 3) {
			buildtd("", "white", "white", "td_three_" + i + "_" + (i + 1) + "_" + (i + 2) + "_", "flattd", "1", "1", line, "clicktd(this,event)");
			if (i < 34) {
				buildtd("", "white", "white", "td_six_" + i + "_" + (i + 1) + "_" + (i + 2) + "_" + (i + 3) + "_" + (i + 4) + "_" + (i + 5) + "_", "flattd", "1", "1", line, "clicktd(this,event)");
			}
		}
		buildtd("", "white", "white", "tdnull", "flattd", "3", "1", line, "clicktd(this,event)");
		tb.appendChild(line);
	}
	for (var i = 1; i <= 5; i++) {
		var line = document.createElement("tr");
		line.id = "tr" + i;
		if (i == 1) {
			buildtd("", "white", "white", "tdnull", "thintd", "1", "5", line, "clicktd(this,event)");
			buildtd("0", "white", "white", "td_one_0_", "fattd", "1", "5", line, "clicktd(this,event)");
		}
		if (i % 2 == 1) {
			buildtd("", "white", "white", "td_two_0_" + (4 - (i + 1) / 2) + "_", "thintd", "1", "1", line, "clicktd(this,event)");
			var startnum = 3 - (i - 1) / 2;
			for (var j = 1; j < 24; j++) {
				if (j % 2 == 0) {
					buildtd("", "white", "white", "td_two_" + (startnum - 3) + "_" + startnum, "thintd", "1", "1", line, "clicktd(this,event)");
				} else {
					buildtd(startnum, "white", "white", "td_one_" + startnum + "_", "fattd", "1", "1", line, "clicktd(this,event)");
					startnum += 3;
				}
			}
			switch (i) {
				case 1:
					buildtd("", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
					buildtd("Third Row", "white", "#227700", "td_line_3", "fattd", "1", "1", line, "clicktd(this,event)");
					buildtd("", "white", "white", "tdnull", "thintd", "1", "5", line, "clicktd(this,event)");
					break;

				case 3:
					buildtd("", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
					buildtd("Second Row", "white", "#227700", "td_line_2", "fattd", "1", "1", line, "clicktd(this,event)");
					break;

				case 5:
					buildtd("", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
					buildtd("First Row", "white", "#227700", "td_line_1", "fattd", "1", "1", line, "clicktd(this,event)");
					break;
				default:
					buildtd("", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
					buildtd("", "white", "white", "tdnull", "fattd", "1", "1", line, "clicktd(this,event)");
			}
		} else {
			buildtd("", "white", "white", "td_three_0_" + (4 - i / 2 - 1) + "_" + (4 - i / 2) + "_", "flattd", "1", "1", line, "clicktd(this,event)");
			for (var j = 1; j <= 12; j++) {
				var num = 4 - i / 2 + 3 * (j - 1);
				buildtd("", "white", "white", "td_two_" + (num - 1) + "_" + num + "_", "flattd", "1", "1", line, "clicktd(this,event)");
				if (j < 12) {
					buildtd("", "white", "white", "td_four_" + (num - 1) + "_" + (num) + "_" + (num + 2) + "_" + (num + 3) + "_", "flattd", "1", "1", line, "clicktd(this,event)");
				} else {
					buildtd("", "white", "white", "tdnull", "flattd", "1", "1", line, "clicktd(this,event)");
					buildtd("", "white", "white", "tdnull", "flattd", "1", "1", line, "clicktd(this,event)");
				}
			}
		}
		tb.appendChild(line);
	}
	{
		var line = document.createElement("tr");
		buildtd("", "white", "white", "tdnull", "flattd", "29", "1", line, "clicktd(this,event)");
		tb.appendChild(line);
	}
	{
		var line = document.createElement("tr");
		buildtd("", "white", "", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
		buildtd("", "white", "", "tdnull", "fattd", "1", "1", line, "clicktd(this,event)");
		buildtd("", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
		for (var i = 1; i <= 3; i++) {
			var num = (i - 1) * 12 + 1;
			buildtd(num + "~" + (num + 11), "white", "#227700", "td_dozen-" + num + "-" + (num + 11), "fattd", "7", "1", line, "clicktd(this,event)");
			buildtd(" ", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
		}
		buildtd("Spin!", "white", "#0000FF", "tdspin", "thintd", "1", "1", line, "spin()");
		buildtd("", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
		tb.appendChild(line);
	}
	{
		var line = document.createElement("tr");
		buildtd("", "white", "", "tdnull", "flattd", "2", "1", line, "clicktd(this,event)");
		buildtd("", "white", "white", "tdnull", "flattd", "27", "1", line, "clicktd(this,event)");
		tb.appendChild(line);
	}
	{
		var line = document.createElement("tr");
		{
			buildtd("", "white", "", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
			buildtd("", "white", "", "tdnull", "fattd", "1", "1", line, "clicktd(this,event)");
			buildtd("", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
			buildtd("1~18", "white", "#227700", "td_half-1-18", "fated", "3", "1", line, "clicktd(this,event)");
			buildtd(" ", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
		}
		{
			buildtd("Odd", "white", "#227700", "td_odd", "fattd", "3", "1", line, "clicktd(this,event)");
			buildtd(" ", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
		}
		{
			buildtd(" ", "white", "#FF0000", "td_red", "fattf", "3", "1", line, "clicktd(this,event)");
			buildtd(" ", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
		}
		{
			buildtd(" ", "white", "#000000", "td_black", "fattd", "3", "1", line, "clicktd(this,event)");
			buildtd(" ", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
		}
		{
			buildtd("19~36", "white", "#227700", "td_half-19-36", "fattd", "3", "1", line, "clicktd(this,event)");
			buildtd(" ", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
		}
		{
			buildtd("Even", "white", "#227700", "td_even", "fattd", "3", "1", line, "clicktd(this,event)");
			buildtd(" ", "white", "white", "tdnull", "thintd", "1", "1", line, "clicktd(this,event)");
		}
		tb.appendChild(line);
	}
	{
		var line = document.createElement("tr");
		buildtd("", "white", "", "tdnull", "flattd", "2", "1", line, "clicktd(this,event)");
		buildtd("", "white", "white", "tdnull", "flattd", "25", "1", line, "clicktd(this,event)");
		tb.appendChild(line);
	}
	draw();
}

function clicktd(obj, event) {


	console.log(obj.id + " clicked");

if( selectedmoney  == 10000000 )
{
	alert("這是假的~ 呵呵~ 驚不驚喜? 意不意外?");
}
else
{

	if (obj.id == "tdnull") {
	} else {



		if (selectedmoney != 0) {


			if (money >= selectedmoney) {

				var x = event.clientX;
				var y = event.clientY;
				var body = document.getElementById("body");
				var imgtag = document.createElement("img");
				imgtag.id = "moneys";
				imgtag.style.position = "absolute";
				imgtag.style.width = "20px";
				imgtag.style.top = (y - 10) + "px";
				imgtag.style.left = (x - 10) + "px";
				imgtag.src = +selectedmoney + ".png";
				body.appendChild(imgtag);
				money -= selectedmoney;
				moneycounts++;

				document.getElementById("money").innerHTML = "Your balance:$" + money;

				for (var i = 0; i < counts; i++) {
					if (obj.id == tdnames[i]) {

						tdmoney[i] += selectedmoney;
						
						break;
					}
				}
			} else {
				if (kidney) {
					if (confirm("Your balance is not enough, do you want to sell your kidney for $200000?(You have " + kidney + " kidney left)")) {
						kidney--;
						money += 200000;

						document.getElementById("money").innerHTML = "Your balance:$" + money;
					}
				} else {
					alert("Look at you, didn't earn any money and lost both of your kidneys. \nWhat a pathetic fellow, your can go die in endless regrets now!");
					location.reload();
				} 
			}
		} else {
			alert("Please choose your bet value!");
		}
	}
}
}


function buildtd(tdText, fontcolor, bgcolor, idname, classname, cols, rows, trobj, onclickname) {
	if (idname != "tdnull") {
		tdnames[counts] = idname;
		tdmoney[counts] = 0;
		counts++;
	}
	var node = document.createTextNode(tdText);
	var cell = document.createElement("td");
	cell.setAttribute("onclick", onclickname);
	cell.style.color = fontcolor;
	if (bgcolor != "") cell.style.background = bgcolor;
	cell.id = idname;
	cell.colSpan = cols;
	cell.rowSpan = rows;
	cell.classList.add(classname);
	cell.append(node);
	trobj.appendChild(cell);
}

function selectmoney(obj) {
	selectedmoney = parseInt(obj.value);
}

function openaward(num, index) {
	console.log("you got " + num);
	var winmoney = 0;
	for (var i = 0; i < counts; i++) {
		if (tdnames[i].includes("_" + num + "_")) {
			if (tdnames[i].includes("one")) {
				winmoney += tdmoney[i] * 36;
			}
			if (tdnames[i].includes("two")) {
				winmoney += tdmoney[i] * 18;
			}
			if (tdnames[i].includes("three")) {
				winmoney += tdmoney[i] * 12;
			}
			if (tdnames[i].includes("four")) {
				winmoney += tdmoney[i] * 9;
			}
			if (tdnames[i].includes("six")) {
				winmoney += tdmoney[i] * 6;
			}
		} else if (tdnames[i].includes("odd") && num % 2 == 1) {
			winmoney += tdmoney[i] * 2;
		} else if (tdnames[i].includes("even") && num % 2 == 0) {
			winmoney += tdmoney[i] * 2;
		} else if (tdnames[i].includes("1-18") && num <= 18 && num >= 1) {
			winmoney += tdmoney[i] * 2;
		} else if (tdnames[i].includes("19-36") && num <= 36 && num >= 19) {
			winmoney += tdmoney[i] * 2;
		} else if (tdnames[i].includes("1-12") && num >= 1 && num <= 12) {
			winmoney += tdmoney[i] * 3;
		} else if (tdnames[i].includes("13-24") && num >= 13 && num <= 24) {
			winmoney += tdmoney[i] * 3;
		} else if (tdnames[i].includes("25-36") && num >= 25 && num <= 36) {
			winmoney += tdmoney[i] * 3;
		} else if (tdnames[i].includes("red") && colors[index] == "red") {
			winmoney += tdmoney[i] * 2;
		} else if (tdnames[i].includes("black") && colors[index] == "black") {
			winmoney += tdmoney[i] * 2;
		} else if (tdnames[i].includes("line_1") && num % 3 == 1) {
			winmoney += tdmoney[i] * 3;
		} else if (tdnames[i].includes("line_2") && num % 3 == 2) {
			winmoney += tdmoney[i] * 3;
		} else if (tdnames[i].includes("line_3") && num % 3 == 0) {
			winmoney += tdmoney[i] * 3;
		}
	}
	money += winmoney;
	console.log("You won $" + winmoney);
	document.getElementById("money").innerHTML = "Your balance:$" + money;
	while (moneycounts--) {
		var imgs = document.getElementById("moneys");
		imgs.parentNode.removeChild(imgs);
	}
	moneycounts = 0;
	for (var i = 0; i < counts; i++) tdmoney[i] = 0;
}

function cheat(num) {
	var index;
	for (var i = 0; i < 37; i++) {
		index = i;
		if (numbers[i] == num) break;
	}
	openaward(num, index);
}