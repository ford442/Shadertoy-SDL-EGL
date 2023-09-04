#include "../../include/vanilla/cropcircle.hpp"

EM_JS(void, ma, (), {
  var dis = set();
  if (dis) dis();dis = set();

  function set() {
    var i;
    var c = document.getElementById("masque");
    var cb = document.getElementById("orig");
    var cc = document.getElementById("temp");
    var ctx = c.getContext("2d");
    var ctxb = cb.getContext("2d");
    var ctxc = cc.getContext("2d");
    var cnP = document.getElementById("cp");
    var flP = document.getElementById("flip");
    var thr = document.getElementById("thr").innerHTML;
    var ra = document.getElementById("pckr").innerHTML;
    var ga = document.getElementById("pckg").innerHTML;
    var ba = document.getElementById("pckb").innerHTML;
    var rb = document.getElementById("pckbr").innerHTML;
    var gb = document.getElementById("pckbg").innerHTML;
    var bb = document.getElementById("pckbb").innerHTML;
    var alf = document.getElementById("alf").innerHTML;
    var alfb = document.getElementById("alfb").innerHTML;
    var ww = document.getElementById("iwid").innerHTML;
    var h = document.getElementById("ihig").innerHTML;
    var vd = document.getElementById("myvideo");
  
    ctxc.drawImage(vd, 0, 0, ww, h);
    var imgData = ctxc.getImageData(0, 0, ww, h);
    ctxb.drawImage(vd, 0, 0, ww, h);
    var rgbdat = new ImageData(ww, h);
    var rgbd = rgbdat.data;
    var imgg = imgData.data;
    for (i = 0; i < (ww * h * 4); i = i + 4) {
      var rgb = (imgg[i] * 0.2126) + (imgg[i + 1] * 0.7152) + (imgg[i + 2] * 0.0722);
      if (rgb > thr) {
        rgbd[i] = ra;
        rgbd[i + 1] = ga;
        rgbd[i + 2] = ba;
        rgbd[i + 3] = alf;
      } else {
        rgbd[i] = rb;
        rgbd[i + 1] = gb;
        rgbd[i + 2] = bb;
        rgbd[i + 3] = alfb;
      }
    }
    ctx.putImageData(rgbdat, 0, 0);

    function Ra() {
      flP.setAttribute("style", "transform: scaleX(1);");
      cnP.setAttribute("style", "transform: scaleY(1);");
    }

    function Rb() {
      flP.setAttribute("style", "transform: scaleX(-1);");
      cnP.setAttribute("style", "transform: scaleY(-1);");
    }
    var knb = document.getElementById("rra");
    var kna = document.getElementById("mainr");
    var knc = document.getElementById("rrb");
    var knd = document.getElementById("rrc");
    var knbb = document.getElementById("rrab");
    var kncb = document.getElementById("rrbb");
    var kndb = document.getElementById("rrcb");
    var rott = 0;
    var rottb = 0;
    var rottc = 0;
    var dsd = false;

    function $rn() {
      if (dsd) {
        return;
      };
      var rate = (kna.innerHTML);

      function rrra(rta) {
        cnP.setAttribute("style", "transform:rotate(" + rta + "deg);");
      }

      function rrrb(rtb) {
        cnP.setAttribute("style", "transform:rotate(" + rtb + "deg);");
      }

      function rrrc(rtc) {
        cnP.setAttribute("style", "transform:rotate(" + rtc + "deg);");
      }
      if ((rott - knd.innerHTML) < 0) {
        rott = (rott + 360 - knd.innerHTML);
      } else {
        rott = rott - knd.innerHTML;
      }
      rrra(rott);
      if ((rottb - knc.innerHTML) < 0) {
        rottb = (rottb + 360 - knc.innerHTML);
      } else {
        rottb = (rottb - knc.innerHTML);
      }
      setTimeout(function() {
        Rb();
        rrrb(rottb);
      }, rate);
      if ((rottc + knb.innerHTML) > 360) {
        rottc = ((rottc + knb.innerHTML) - 360);
      } else {
        rottc = (rottc + knb.innerHTML);
      }
      setTimeout(function() {
        Ra();
        rrrc(rottc);
      }, rate);
      setTimeout(function() {
        $rn();
      }, rate);
    }
    $rn();
    document.getElementById("di").onclick = function() {
      dsd = true;
      set();
    };
    return () => {
      dsd = true;
    };
  }
});

int main() {
  ma();
  return 1;
}
