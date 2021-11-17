MyModule={
canvas:(function(){
var aCanvas=document.getElementById('canvas');
aGlCtx=aCanvas.getContext('webgl2',{alpha:false,premultipliedAlpha:false,depth:false,antialias:false,preserveDrawingBuffer:false}); 
return aCanvas;
})(),};
const OccViewerModuleInitialized=createModule(MyModule);
