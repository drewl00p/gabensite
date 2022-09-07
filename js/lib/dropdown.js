let dropdown = document.querySelector('.dropdown')
let dropdown_toggle = false;

dropdown.addEventListener('mouseenter', (e) => {
  if (dropdown.classList.contains('closed')) {
    dropdown.classList.remove('closed')
  }
})
dropdown.addEventListener('mouseleave', (e) => {
  if (!dropdown.classList.contains('closed') && dropdown_toggle === false) {
    dropdown.classList.add('closed')   
  } 
})
dropdown.addEventListener('click', (e) => {
  if (!dropdown_toggle) {
    dropdown_toggle = true;
  } else if (dropdown_toggle) {
    dropdown_toggle = false;
  }
})