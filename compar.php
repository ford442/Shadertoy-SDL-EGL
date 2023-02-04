<head>
<link rel=preconnect href=https://wasm.noahcohn.com/>
<link rel=preconnect href=https://js.1ink.us/>
<link rel=preconnect href=https://glsl.1ink.us/>
<link rel=preconnect href=https://css.1ink.us/>
<meta name=viewport content='width=device-width, initial-scale=1.0'/>
<title>B3HD</title>
<link crossorigin rel='stylesheet' href='https://css.1ink.us/sh1.1iss'/>
</head>
<body>
<nav id=menu>
<section class=menu-section id=menu-sections>
<br>
<div style='text-align:center;'>
TIMESLIDER<br>(Seconds between video changes)</div>
<br><br>
<ul class=menu-section-list>
<div id=mnu>
<div id=slideframe>
<input type=text id=timeslider>
</div></div></ul></section></nav>
<main id=panel>
<iframe src=./bezz.1ink id=circle title='Circular mask'></iframe>
<input type=button id=menuBtn style='background-color:black;position:absolute;display:block;left:3%;top:5%;z-index:999999;border:6px solid #e7e7e7;border-radius:20%;' />
<input type=button id=musicBtn style='background-color:cyan;position:absolute;display:block;left:3%;bottom:5%;z-index:999999;border:6px solid green;border-radius:20%;' />
<div class=emscripten id=status></div>
<div class=emscripten>
<progress value=0 max=100 id=progress></progress>
</div>
<input type=checkbox id=di hidden />
<div hidden=true id=path>./all/melt</div>
<div id=iwid hidden>0</div>
<div id=ihig hidden>0</div>
<div id=pmhig hidden>0</div>
<div id=wid hidden>0</div>
<div id=hig hidden>0</div>
<div id=lwid hidden>0</div>
<div id=lhig hidden>0</div>
<div id=ihid hidden>0</div>
<div id=tim hidden>1750</div>
<div id=shut hidden>1</div>
<div id=isrc hidden>./intro.mp4</div>
<div id=idur hidden>0</div>
<div id=itim hidden>0</div>
<div id=wrap>
<div id=contain1>
<canvas class=emscripten id=scanvas style='opacity:1.0;pointer-events:auto;display:block;position:absolute;z-index:999994;background-color:rgba(1,1,1,0);top:0;height:100vh;width:100vh;image-rendering:auto;'></canvas>
</div>
<div id=contain2>
<canvas id=acanvas style='pointer-events:auto;cursor:url(cursor.cur),auto;display:block;z-index:999994;position:absolute;height:100vh;width:100vh;margin-left:auto;margin-right:auto;background-color:rgba(1,1,1,0);top:0;image-rendering:auto;'></canvas>
<canvas id=bcanvas style='pointer-events:none;display:block;z-index:999994;position:absolute;height:100vh;width:100vh;margin-left:auto;margin-right:auto;background-color:rgba(1,1,1,0);top:0;image-rendering:auto;'></canvas>
</div></div>
</main>
<div id=vidWrapA>
<video hidden muted src=./intro.mp4 crossorigin id=mv preload=auto style='pointer-events:none;' />
</div>
<div id=vidWrapB>
<video hidden muted src=./intro.mp4 crossorigin id=ldv preload=auto style='pointer-events:none;' />
</div>
<audio crossorigin id=track preload=none hidden style='pointer-events:none;'></audio>
<script async=true crossorigin src=https://wasm.noahcohn.com/test/g3020.1ijs></script>
</body>
