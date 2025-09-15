#include "web_js.h"

String getDrumMachineJS() {
  String js = "let sequence=Array(8).fill().map(()=>Array(16).fill(false));";
  js += "let isPlaying=false,currentBPM=120,isEditable=true;";
  
  // Simple clear function
  js += "function clearAllSteps(){for(let t=0;t<8;t++){for(let s=0;s<16;s++){sequence[t][s]=false;let btn=document.getElementById(`step_${t}_${s}`);if(btn){btn.className='step-button';}}}}";
  
  // Immediate drum trigger
  js += "function triggerDrum(id){fetch('/trigger',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'drum='+id}).catch(e=>console.error('Drum error:',e));}";
  
  // Simple step toggle
  js += "function toggleStep(track,step){if(!isEditable)return;let btn=document.getElementById(`step_${track}_${step}`);sequence[track][step]=!sequence[track][step];btn.classList.toggle('active',sequence[track][step]);console.log(`Step ${track}-${step}:`,sequence[track][step]);}";
  
  // Edit mode toggle
  js += "function setEditMode(editable){isEditable=editable;let grid=document.querySelector('.sequence-grid');if(grid){grid.classList.toggle('playing-mode',!editable);}}";
  
  // Lightweight sync - reset server then send only active steps
  js += "function syncToServer(){";
  js += "console.log('=== SYNC START ===');";
  js += "return fetch('/transport',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'action=reset'})";
  js += ".then(()=>{";
  js += "console.log('Server reset completed');";
  js += "let activeSteps=[];";
  js += "for(let t=0;t<8;t++){";
  js += "for(let s=0;s<16;s++){";
  js += "if(sequence[t][s]){";
  js += "activeSteps.push({t,s});";
  js += "}}}";
  js += "console.log('Active steps to send:',activeSteps.length);";
  js += "if(activeSteps.length===0)return Promise.resolve();";
  js += "let sendNext=(index)=>{";
  js += "if(index>=activeSteps.length)return Promise.resolve();";
  js += "let step=activeSteps[index];";
  js += "return fetch('/sequence',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:`track=${step.t}&step=${step.s}&active=true`})";
  js += ".then(()=>sendNext(index+1));";
  js += "};";
  js += "return sendNext(0);";
  js += "}).then(()=>{";
  js += "console.log('✅ Sync completed');";
  js += "});";
  js += "}";
  
  // Transport control without visual tracking
  js += "function transportControl(action){";
  js += "console.log('Transport:',action);";
  js += "if(action==='play'&&!isPlaying){";
  js += "let hasActive=false;";
  js += "for(let t=0;t<8&&!hasActive;t++){for(let s=0;s<16;s++){if(sequence[t][s]){hasActive=true;break;}}}";
  js += "if(!hasActive){alert('No steps selected!');return;}";
  js += "console.log('Starting playback...');";
  js += "setEditMode(false);";
  js += "syncToServer().then(()=>{";
  js += "return fetch('/transport',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'action=play'});";
  js += "}).then(r=>r.json()).then(d=>{";
  js += "console.log('Play started:',d);";
  js += "isPlaying=true;";
  js += "document.getElementById('playStatus').textContent='Playing';";
  js += "document.getElementById('currentStep').textContent='Playing...';";
  js += "}).catch(e=>{";
  js += "console.error('Play failed:',e);";
  js += "setEditMode(true);";
  js += "});";
  js += "return;";
  js += "}";
  js += "if(action==='stop'){isPlaying=false;setEditMode(true);document.getElementById('playStatus').textContent='Stopped';document.getElementById('currentStep').textContent='-';}";
  js += "if(action==='reset'){isPlaying=false;clearAllSteps();setEditMode(true);document.getElementById('playStatus').textContent='Stopped';document.getElementById('currentStep').textContent='-';}";
  js += "if(action!=='play'){";
  js += "fetch('/transport',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'action='+action}).catch(e=>console.error('Transport error:',e));";
  js += "}";
  js += "}";
  
  // BPM update
  js += "function updateBPM(val){currentBPM=parseInt(val);document.getElementById('bpmValue').textContent=val;document.getElementById('currentBPM').textContent=val;fetch('/bpm',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'bpm='+val}).catch(e=>{});}";
  
  // Simple initialization
  js += "document.addEventListener('DOMContentLoaded',()=>{";
  js += "console.log('Drum machine ready - No visual tracking mode');";
  js += "clearAllSteps();";
  js += "setEditMode(true);";
  js += "});";
  
  // iPad touch support
  js += "document.addEventListener('touchstart',e=>{";
  js += "if(e.target.classList.contains('step-button')){";
  js += "e.preventDefault();";
  js += "let parts=e.target.id.split('_');";
  js += "if(parts.length===3){";
  js += "toggleStep(parseInt(parts[1]),parseInt(parts[2]));";
  js += "}";
  js += "}";
  js += "},{passive:false});";
  
  js += "document.addEventListener('touchstart',e=>{";
  js += "if(e.target.classList.contains('drum-pad')){";
  js += "e.preventDefault();";
  js += "let drumId=Array.from(document.querySelectorAll('.drum-pad')).indexOf(e.target);";
  js += "if(drumId>=0)triggerDrum(drumId);";
  js += "}";
  js += "},{passive:false});";
  
  // Keyboard shortcuts
  js += "document.addEventListener('keydown',e=>{if(e.key>='1'&&e.key<='8')triggerDrum(parseInt(e.key)-1);if(e.code==='Space'){e.preventDefault();transportControl(isPlaying?'stop':'play');}if(e.key==='r'||e.key==='R')transportControl('reset');});";
  
  return js;
}