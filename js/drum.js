document.querySelector('#drumBtn').addEventListener('click',function(){
window.open('./drum');
});

let drumTempo=new BroadcastChannel('tempo');

drumTempo.addEventListener('message',ea=>{
var tmp0=ea.data.data;
Module.ccall('tempoSet',null,["Number"],[tmp0]);
});
