let s = Snap(".svg"); /*поле*/
var bigCircle = s.circle(150, 150, 100); /*большой круг*/
bigCircle.attr({ /*парамерты*/
  fill: "#bada55",
  stroke: "#fff", /*цвет*/
  strokeWidth: 5
});
var smallCircle = s.circle(150, 100, 70); /*маленькой круг 100, 150, 70*/
var discs = s.group(smallCircle, s.circle(150, 200, 70)); /*группа диски*/
discs.attr({
  fill: "#fff"
});
bigCircle.attr({/*маска, большой белый, диски цветные*/
  mask: discs
});
smallCircle.animate({r: 50}, 1000);/*аниммация уменьшения левого до r 50*/
discs.select("circle:nth-child(2)").animate({r: 50}, 1000); /*второй*/
var p = s.path("M10-5-10,15M15,0,0,15M0-5-20,15").attr({/*шаблон*/
  fill: "none",
  stroke: "#bada55",
  strokeWidth: 5
});
p = p.pattern(0, 0, 10, 10);
bigCircle.attr({
  fill: p /*применение шаблона*/
});
discs.attr({
  fill: Snap("#pattern") /*второй шаблон (зачем)*/
});
discs.attr({fill: "r()#fff-#000"}); /*белый по радиусу*/
discs.attr({fill: "R(150, 150, 100)#fff-#000"});/*размытый по радиусу*/