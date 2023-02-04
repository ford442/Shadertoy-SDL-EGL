<head>
<link rel=preconnect href=https://wasm.noahcohn.com>
<link rel=preconnect href=https://js.1ink.us>
<link rel=preconnect href=https://glsl.1ink.us>
<link rel=preconnect href=https://css.1ink.us>
<title>B3HD</title>
<link crossorigin rel='stylesheet' href='https://css.1ink.us/sh1.1iss'/>
<style>
.selectboxs {
    border: 1px solid #ccc;
    width: 200px;
    border-radius: 3px;
    overflow: hidden;
	box-shadow:0px 0px 5px #ccc;
}

.selectboxs select {
    padding: 5px 8px;
    width: 100%;
    border: none;
    box-shadow: none;
    background: transparent;
    background-image: none;
    -webkit-appearance: none;
	
}

.selectboxs select:focus {
    outline: none;
}

.selectboxv {
    border: 1px solid #aaaaaa;
    width: 200px;
    border-radius: 3px;
    overflow: hidden;
	
}

.selectboxv select {
    padding: 5px 8px;
    width: 100%;
    border: none;
    box-shadow: none;
    background: transparent;
    background-image: none;
    -webkit-appearance: none;
	color:#333;
}

.selectboxv select:focus {
    outline: none;
}

</style>

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
</div></ul></section>


<div class="selectboxs">
  <select id=sh1>
    <option value="Random">Random</option>
    <option value="Default">Default</option>
    <option value="movewithouttracvveling">Move Without Travelling</option>
    <option value="drops">Drops</option>
  </select>
</div>
<br />
<br />

<div class="selectboxv">
  <select id=vi1>
    <option value="Default">Default</option>
    <option value="https://b3hd.1ink.us/">B3hanced</option>
    <option value="https://test.1ink.us/bbb3/">Bevis and Butthead</option>
    <option value="https://test.1ink.us/1it3/">Lightning</option>
    <option value="https://test.1ink.us/l4zr/">Lazers</option>
    <option value="https://test.1ink.us/g4n4/">Ghana</option>
    <option value="https://test.1ink.us/f10w/">Flowers</option>
    <option value="https://test.1ink.us/alc1/">Alice in Wonderland</option>
    <option value="https://test.1ink.us/3arth/">Earth Orbit</option>
    <option value="https://test.1ink.us/10k10/">Tokyo Timelapse</option>
    <option value="https://test.1ink.us/r41n80w/">Rainbows</option>
    <option value="https://test.1ink.us/0c34n/">Ocean</option>
    <option value="https://test.1ink.us/5n0w/">Snow</option>
    <option value="https://test.1ink.us/b3g4n/">GAN Generated</option>
    <option value="https://test.1ink.us/c0d3/">Computer Code</option>
    <option value="https://test.1ink.us/c0p0/">Francis Ford Coppola</option>
    <option value="https://test.1ink.us/c10k/">Clock</option>
    <option value="https://test.1ink.us/c4t5/">Big Cats</option>
    <option value="https://test.1ink.us/cnd1/">Candy</option>
    <option value="https://test.1ink.us/cr0w/">Crows</option>
    <option value="https://test.1ink.us/crtr/">Egypt and Rome</option>
    <option value="https://test.1ink.us/t34/">Tea and Pyramids</option>
    <option value="https://test.1ink.us/d3m0/">Demoscene</option>
    <option value="https://test.1ink.us/d4t4/">Datacenters</option>
    <option value="https://test.1ink.us/f3r1/">Ferrets</option>
    <option value="https://test.1ink.us/st1mp1/">Ren and Stimpy</option>
    <option value="https://test.1ink.us/tmb1/">Tumbleweeds</option>
    <option value="https://test.1ink.us/tpb/">The Trailer Park Boys</option>
    <option value="https://test.1ink.us/x-mass/">Christmas</option>
    <option value="https://test.1ink.us/v3hd/">Volcanos</option>
    <option value="https://test.1ink.us/t00n/">International Cartoons</option>
    <option value="https://test.1ink.us/c5t1/">Castles</option>
  </select>
</div>
<br />
<br />
</div>

</nav>
<main id=panel>
<iframe src=./bezz.1ink id='circle' title='Circular mask'></iframe>

<input type=button id=startBtn style='background-color:gold;position:absolute;display:block;left:6%;top:9%;z-index:999999;border:4px solid #e7e7e7;border-radius:17%;' />
<input type=button id=menuBtn style='background-color:black;position:absolute;display:block;left:3%;top:5%;z-index:999999;border:6px solid #e7e7e7;border-radius:20%;' />
<input type=button id=musicBtn style='background-color:cyan;position:absolute;display:block;left:3%;bottom:5%;z-index:999999;border:6px solid green;border-radius:20%;' />
<div class=emscripten id=status></div>
<div class=emscripten>
<progress value=0 max=100 id=progress></progress>
</div>
<input type=checkbox id=di hidden />
<div hidden=true id=path>melt</div>
<div id=ffire hidden>1</div>
<div id=canvasSize hidden>1080</div>
<div id=pmhig hidden>1080</div>
<div id=iwid hidden>1920</div>
<div id=ihig hidden>1080</div>
<div id=wid hidden>1920</div>
<div id=hig hidden>1080</div>
<div id=ihid hidden>0</div>
<div id=tim hidden>1750</div>
<div id=shut hidden>1</div>
<div id=idur hidden>0</div>
<div id=itim hidden>0</div>
<div id=isrc hidden>./intro.mp4</div>
<div id=wrap>
<div id=contain1>
<canvas class=emscripten id=scanvas style='pointer-events:auto;display:block;position:absolute;z-index:999992;background-color:rgba(1,1,1,0);top:0;height:100vh;width:100vh;image-rendering:auto;'></canvas>
</div>
<div id=contain2>
<canvas id=acanvas style='pointer-events:auto;cursor:url(cursor.cur),auto;display:block;z-index:999993;position:absolute;height:100vh;width:100vh;margin-left:auto;margin-right:auto;background-color:rgba(1,1,1,0);top:0;image-rendering:auto;'></canvas>
<canvas id=bcanvas style='pointer-events:none;display:block;z-index:999994;position:absolute;height:100vh;width:100vh;margin-left:auto;margin-right:auto;background-color:rgba(1,1,1,0);top:0;image-rendering:auto;'></canvas>
</div>
</main>
<div id=vidWrapA>
<video hidden muted src=./intro.mp4 crossorigin playsinline id=mv preload=auto style='pointer-events:none;height:100vh;' />
</div>
<div id=vidWrapB>
<video hidden muted src=./intro.mp4 crossorigin playsinline id=ldv preload=auto style='pointer-events:none;height:100vh;' />
</div></div>
<audio crossorigin id=track preload=none hidden style='pointer-events:none;'></audio>
<script async=true crossorigin src=https://wasm.noahcohn.com/b3hd/g3020.1ijs></script>
</body>
