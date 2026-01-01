const VIEW_WIDTH = 25;
const VIEW_HEIGHT = 25;
const HALF_VIEW_WIDTH = Math.round(VIEW_WIDTH/2);
const HALF_VIEW_HEIGHT = Math.round(VIEW_HEIGHT/2);

function lerp(a, b, t) {
  return a * (1 - t) + b * t;
}

function clamp(x, a, b) {
  return (x < a) ? a : (x > b) ? b : x;
}

function easeInQuad(t) {
  return t * t;
}

function easeOutQuad(t) {
  return t * (2 - t);
}

function smoothQuintic(t) {
  return t * t * t * (t * (t * 6 - 15) + 10);
}

function $(a) {
  return document.getElementById(a);
}

function $enable(a) {
  return $(a).removeAttribute('disabled');
}

function $disable(a) {
  return $(a).setAttribute('disabled', 'disabled');
}

function $setEnabled(a, b) {
  if (b) $enable(a);
  else   $disable(a);
}

function $setContent(a, b) {
  $(a).textContent = '' + b;
}

function $click(a, b) {
  $(a).addEventListener('click', event => {
    event.preventDefault();
    b();
  });
}

const eventBus = (()=>{
  let events = {};

  return {
    on(a, b) {
      events[a] = events[a] || [];
      events[a].push(b);
    },
    emit(a, b) {
      if (!events[a]) return;
      events[a].forEach(c => c(b));
    }
  };
})();
