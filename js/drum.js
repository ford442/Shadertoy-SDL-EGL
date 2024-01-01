document.querrySelector('#drumBtn').addEventListener('click',function(){
window.open('./drum');
});

let drumTempo=new BroadcastChannel('tempo');

drumTempo.addEventListener('message',ea=>{
console.log(ea);
console.log(ea.data);
console.log(ea.data.data);
});
