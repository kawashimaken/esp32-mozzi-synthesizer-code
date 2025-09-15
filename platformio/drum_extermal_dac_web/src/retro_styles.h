#ifndef RETRO_STYLES_H
#define RETRO_STYLES_H

#include <Arduino.h>

String getCSS() {
  String css = "";
  
  // Retro Mac color palette
  css += ":root{";
  css += "--mac-gray:#c0c0c0;";
  css += "--mac-dark-gray:#808080;";
  css += "--mac-light-gray:#e0e0e0;";
  css += "--mac-black:#000000;";
  css += "--mac-white:#ffffff;";
  css += "--mac-blue:#0000ff;";
  css += "--mac-green:#00ff00;";
  css += "--mac-red:#ff0000;";
  css += "--mac-yellow:#ffff00;";
  css += "}";
  
  // Base layout (increased font size)
  css += "body{";
  css += "font-family:Monaco,Consolas,monospace;";
  css += "font-size:clamp(16px,3vw,20px);";
  css += "background:var(--mac-gray);";
  css += "background-image:repeating-linear-gradient(45deg,var(--mac-gray) 0px,var(--mac-gray) 1px,var(--mac-light-gray) 1px,var(--mac-light-gray) 2px);";
  css += "color:var(--mac-black);";
  css += "margin:0;";
  css += "padding:clamp(15px,3vw,25px);";
  css += "box-sizing:border-box;";
  css += "min-height:100vh;";
  css += "}";
  
  css += "*{box-sizing:border-box}";
  css += ".container{max-width:100%;margin:0 auto;width:100%}";
  
  // Mac-style title (larger font size)
  css += "h1{";
  css += "font-family:Monaco,Consolas,monospace;";
  css += "font-size:clamp(24px,5vw,32px);";
  css += "font-weight:bold;";
  css += "letter-spacing:1.5px;";
  css += "background:linear-gradient(180deg,var(--mac-light-gray) 0%,var(--mac-gray) 50%,var(--mac-dark-gray) 100%);";
  css += "border:2px outset var(--mac-gray);";
  css += "color:var(--mac-black);";
  css += "text-align:center;";
  css += "margin-bottom:clamp(20px,4vw,35px);";
  css += "padding:clamp(12px,3vw,18px);";
  css += "text-shadow:1px 1px 0 var(--mac-white),-1px -1px 0 var(--mac-dark-gray);";
  css += "position:relative;";
  css += "box-shadow:inset 1px 1px 0 var(--mac-white),inset -1px -1px 0 var(--mac-dark-gray);";
  css += "}";
  
  // Title bar decoration
  css += "h1:before{";
  css += "content:\"●\";";
  css += "position:absolute;";
  css += "left:12px;";
  css += "top:50%;";
  css += "transform:translateY(-50%);";
  css += "color:#ff0000;";
  css += "font-size:16px;";
  css += "text-shadow:1px 1px 0 var(--mac-white);";
  css += "}";
  
  css += "h1:after{";
  css += "content:\"●\";";
  css += "position:absolute;";
  css += "right:12px;";
  css += "top:50%;";
  css += "transform:translateY(-50%);";
  css += "color:#32CD32;";
  css += "font-size:16px;";
  css += "text-shadow:1px 1px 0 var(--mac-white);";
  css += "}";
  
  // Section
  css += ".section{";
  css += "background:var(--mac-light-gray);";
  css += "border:2px inset var(--mac-gray);";
  css += "margin-bottom:clamp(15px,3vw,25px);";
  css += "position:relative;";
  css += "}";
  
  css += ".section h2{";
  css += "font-family:Monaco,Consolas,monospace;";
  css += "font-size:clamp(16px,3.5vw,22px);";
  css += "font-weight:bold;";
  css += "letter-spacing:0.8px;";
  css += "background:linear-gradient(180deg,var(--mac-light-gray) 0%,var(--mac-gray) 100%);";
  css += "border:1px outset var(--mac-gray);";
  css += "border-bottom:2px inset var(--mac-gray);";
  css += "color:var(--mac-black);";
  css += "margin:0 0 clamp(15px,3vw,20px) 0;";
  css += "padding:clamp(10px,2.5vw,15px) clamp(15px,3vw,20px);";
  css += "text-shadow:1px 1px 0 var(--mac-white);";
  css += "position:relative;";
  css += "}";
  
  css += ".section h2:before{";
  css += "content:\"▦\";";
  css += "position:absolute;";
  css += "left:6px;";
  css += "top:50%;";
  css += "transform:translateY(-50%);";
  css += "color:var(--mac-dark-gray);";
  css += "font-size:12px;";
  css += "}";
  
  css += ".section>:not(h2){padding:0 clamp(15px,3vw,20px) clamp(15px,3vw,20px);}";
  
  // Drum pads (larger font size and overall pad size)
  css += ".drum-pads{";
  css += "display:grid;";
  css += "grid-template-columns:repeat(auto-fit,minmax(clamp(100px,15vw,140px),1fr));";
  css += "gap:clamp(12px,2.5vw,16px);";
  css += "margin-bottom:clamp(20px,4vw,25px);";
  css += "}";
  
  css += ".drum-pad{";
  css += "font-family:Monaco,Consolas,monospace;";
  css += "font-size:clamp(14px,2.5vw,18px);";
  css += "font-weight:bold;";
  css += "letter-spacing:0.8px;";
  css += "padding:clamp(12px,3vw,18px);";
  css += "border:3px outset var(--mac-gray);";
  css += "background:linear-gradient(145deg,var(--mac-light-gray) 0%,var(--mac-gray) 50%,var(--mac-dark-gray) 100%);";
  css += "cursor:pointer;";
  css += "color:var(--mac-black);";
  css += "min-height:clamp(55px,8vw,70px);";
  css += "display:flex;";
  css += "align-items:center;";
  css += "justify-content:center;";
  css += "text-shadow:1px 1px 0 var(--mac-white),-1px -1px 0 var(--mac-dark-gray);";
  css += "transition:all 0.1s ease;";
  css += "position:relative;";
  css += "box-shadow:2px 2px 4px rgba(0,0,0,0.3),inset 1px 1px 0 var(--mac-white),inset -1px -1px 0 var(--mac-dark-gray);";
  css += "}";
  
  css += ".drum-pad:hover{";
  css += "background:linear-gradient(145deg,var(--mac-gray) 0%,var(--mac-dark-gray) 50%,#606060 100%);";
  css += "border:3px outset var(--mac-dark-gray);";
  css += "}";
  
  css += ".drum-pad:active{";
  css += "border:3px inset var(--mac-gray);";
  css += "background:linear-gradient(145deg,var(--mac-dark-gray) 0%,var(--mac-gray) 50%,var(--mac-light-gray) 100%);";
  css += "transform:translate(2px,2px);";
  css += "box-shadow:inset 2px 2px 4px rgba(0,0,0,0.3);";
  css += "text-shadow:0px 0px 0 transparent;";
  css += "}";
  
  // Transport buttons (increased size and font size)
  css += ".transport-controls{";
  css += "display:flex;";
  css += "flex-wrap:wrap;";
  css += "justify-content:center;";
  css += "gap:clamp(12px,2.5vw,16px);";
  css += "margin-bottom:clamp(20px,4vw,25px);";
  css += "}";
  
  css += ".transport-btn{";
  css += "font-family:Monaco,Consolas,monospace;";
  css += "font-size:clamp(14px,2.8vw,18px);";
  css += "font-weight:bold;";
  css += "letter-spacing:0.8px;";
  css += "padding:clamp(12px,2.5vw,16px) clamp(20px,4vw,28px);";
  css += "border:3px outset var(--mac-gray);";
  css += "cursor:pointer;";
  css += "min-height:clamp(48px,7vw,56px);";
  css += "text-shadow:1px 1px 0 var(--mac-white);";
  css += "transition:all 0.1s ease;";
  css += "}";
  
  css += ".play-btn{";
  css += "background:linear-gradient(145deg,#90EE90,#32CD32);";
  css += "color:var(--mac-black);";
  css += "}";
  
  css += ".stop-btn{";
  css += "background:linear-gradient(145deg,#FFB6C1,#FF69B4);";
  css += "color:var(--mac-black);";
  css += "}";
  
  css += ".reset-btn{";
  css += "background:linear-gradient(145deg,#FFE4B5,#FFA500);";
  css += "color:var(--mac-black);";
  css += "}";
  
  css += ".transport-btn:hover{";
  css += "filter:brightness(0.9);";
  css += "}";
  
  css += ".transport-btn:active{";
  css += "border:3px inset var(--mac-gray);";
  css += "transform:translate(1px,1px);";
  css += "}";
  
  // Sequencer
  css += ".sequence-container{";
  css += "overflow-x:auto;";
  css += "margin-bottom:clamp(15px,3vw,20px);";
  css += "border:2px inset var(--mac-gray);";
  css += "background:var(--mac-white);";
  css += "padding:clamp(8px,2vw,12px);";
  css += "}";
  
  css += ".sequence-grid{";
  css += "display:grid;";
  css += "grid-template-columns:clamp(80px,15vw,120px) repeat(16,1fr);";
  css += "gap:clamp(2px,0.5vw,4px);";
  css += "transition:opacity 0.3s ease;";
  css += "width:100%;";
  css += "min-width:400px;";
  css += "}";
  
  css += ".sequence-grid.playing-mode{";
  css += "opacity:0.8;";
  css += "background:rgba(192,192,192,0.1);";
  css += "}";
  
  // Track label (increased font size)
  css += ".track-label{";
  css += "font-family:Monaco,Consolas,monospace;";
  css += "font-size:clamp(12px,2vw,16px);";
  css += "font-weight:bold;";
  css += "letter-spacing:0.5px;";
  css += "padding:clamp(6px,1.5vw,10px);";
  css += "background:var(--mac-gray);";
  css += "border:1px outset var(--mac-gray);";
  css += "text-align:center;";
  css += "display:flex;";
  css += "align-items:center;";
  css += "justify-content:center;";
  css += "min-height:clamp(35px,5vw,45px);";
  css += "text-shadow:1px 1px 0 var(--mac-white);";
  css += "}";
  
  css += ".track-label:first-child{";
  css += "background:var(--mac-dark-gray);";
  css += "color:var(--mac-white);";
  css += "text-shadow:1px 1px 0 var(--mac-black);";
  css += "}";
  
  // Step buttons (increased size)
  css += ".step-button{";
  css += "aspect-ratio:1;";
  css += "min-width:clamp(24px,4.5vw,40px);";
  css += "min-height:clamp(24px,4.5vw,40px);";
  css += "border:2px outset var(--mac-gray);";
  css += "background:linear-gradient(145deg,var(--mac-light-gray) 0%,var(--mac-gray) 50%,var(--mac-dark-gray) 100%);";
  css += "cursor:pointer;";
  css += "transition:all 0.1s ease;";
  css += "display:flex;";
  css += "align-items:center;";
  css += "justify-content:center;";
  css += "position:relative;";
  css += "box-shadow:1px 1px 2px rgba(0,0,0,0.3),inset 1px 1px 0 var(--mac-white),inset -1px -1px 0 var(--mac-dark-gray);";
  css += "}";
  
  css += ".step-button.active{";
  css += "background:linear-gradient(145deg,#98FB98 0%,#32CD32 50%,#228B22 100%);";
  css += "border:2px inset var(--mac-green);";
  css += "box-shadow:inset 2px 2px 3px rgba(0,0,0,0.4),inset -1px -1px 0 #90EE90;";
  css += "}";
  
  css += ".step-button.active:after{";
  css += "content:\"◉\";";
  css += "position:absolute;";
  css += "color:#00ff00;";
  css += "font-size:clamp(8px,1.5vw,12px);";
  css += "text-shadow:0 0 clamp(3px,0.8vw,5px) #00ff00;";
  css += "}";
  
  css += ".step-button:hover:not(.active){";
  css += "background:linear-gradient(145deg,var(--mac-gray) 0%,var(--mac-dark-gray) 50%,#606060 100%);";
  css += "}";
  
  css += ".step-button:active{";
  css += "border:2px inset var(--mac-gray);";
  css += "transform:translate(1px,1px);";
  css += "box-shadow:inset 1px 1px 2px rgba(0,0,0,0.4);";
  css += "}";
  
  css += ".playing-mode .step-button{";
  css += "cursor:not-allowed;";
  css += "opacity:0.8;";
  css += "}";
  
  // BPM control (increased font size and control size)
  css += ".bpm-control{";
  css += "font-family:Monaco,Consolas,monospace;";
  css += "font-size:clamp(14px,2.8vw,18px);";
  css += "font-weight:bold;";
  css += "text-align:center;";
  css += "margin-top:clamp(15px,3vw,20px);";
  css += "display:flex;";
  css += "flex-wrap:wrap;";
  css += "justify-content:center;";
  css += "align-items:center;";
  css += "gap:clamp(12px,2.5vw,16px);";
  css += "}";
  
  css += ".bpm-control input[type=range]{";
  css += "width:clamp(150px,35vw,240px);";
  css += "height:clamp(28px,4vw,36px);";
  css += "border:2px inset var(--mac-gray);";
  css += "background:var(--mac-white);";
  css += "appearance:none;";
  css += "-webkit-appearance:none;";
  css += "}";
  
  css += "#bpmValue{";
  css += "font-family:Monaco,Consolas,monospace;";
  css += "font-weight:bold;";
  css += "min-width:clamp(35px,5vw,45px);";
  css += "font-size:clamp(14px,2.8vw,18px);";
  css += "background:var(--mac-white);";
  css += "border:1px inset var(--mac-gray);";
  css += "padding:clamp(4px,1vw,8px) clamp(8px,2vw,12px);";
  css += "}";
  
  // Status (increased font size)
  css += ".status-info{";
  css += "display:grid;";
  css += "grid-template-columns:repeat(auto-fit,minmax(clamp(150px,30vw,200px),1fr));";
  css += "gap:clamp(12px,2.5vw,16px);";
  css += "}";
  
  css += ".status-info p{";
  css += "font-family:Monaco,Consolas,monospace;";
  css += "font-size:clamp(12px,2.2vw,16px);";
  css += "font-weight:bold;";
  css += "margin:clamp(6px,1.5vw,10px) 0;";
  css += "background:var(--mac-white);";
  css += "border:2px inset var(--mac-gray);";
  css += "padding:clamp(10px,2.5vw,14px);";
  css += "text-align:center;";
  css += "box-shadow:inset 1px 1px 2px rgba(0,0,0,0.2);";
  css += "}";
  
  // iPad-specific responsive adjustments
  css += "@media (min-width: 768px) and (max-width: 1024px) {";
  css += "  body{font-size:18px;}";
  css += "  .sequence-grid{grid-template-columns:clamp(90px,12vw,110px) repeat(16,1fr);}";
  css += "  .drum-pads{grid-template-columns:repeat(4,1fr);}";
  css += "  .drum-pad{font-size:16px;min-height:65px;}";
  css += "  .transport-btn{font-size:16px;min-height:52px;}";
  css += "  .step-button{min-width:36px;min-height:36px;}";
  css += "}";
  
  css += "@media (min-width: 480px) and (max-width: 767px) {";
  css += "  .sequence-grid{grid-template-columns:clamp(70px,18vw,85px) repeat(16,1fr);}";
  css += "  .drum-pads{grid-template-columns:repeat(4,1fr);}";
  css += "}";
  
  css += "@media (max-width: 479px) {";
  css += "  .sequence-grid{grid-template-columns:clamp(55px,20vw,75px) repeat(16,1fr);}";
  css += "  .drum-pads{grid-template-columns:repeat(2,1fr);}";
  css += "  .transport-controls{flex-direction:column;}";
  css += "}";
  
  return css;
}

#endif