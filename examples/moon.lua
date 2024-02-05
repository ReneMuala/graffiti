gradient = gradient.linear(10, 10, 90, 90) {
	10, pink,
	50, violet,
	90, red
}

star = g.image(128px,128px)
	.moveto(50,0)
	.lineto(60,40)
	.lineto(100,40)
	.lineto(65,60)
	.lineto(75,100)
	.lineto(50,75)
	.lineto(25,100)
	.lineto(35,60)
	.lineto(0,40)
	.lineto(40,40)
	.closepath()
		.stroke(0x55FFFFFF, { width = 5px })
	.close()

g.image(512px,512px)
	.fill(black)
	.fill(star)
	.circle(50,50,40)
		.fill(gradient)
	.circle(60,40,30)
		.fill(black)
		.fill(star)
	.export(moon.png)
	.close()