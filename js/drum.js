document.querySelector('#drumBtn').addEventListener('click',function(){
window.open('./drum');
});

let drumTempo=new BroadcastChannel('tempo');

drumTempo.addEventListener('message',ea=>{
console.log('ea:',ea);
console.log('ea.data:',ea.data);
console.log('ea.data.data:',ea.data.data);
});
