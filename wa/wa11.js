const displayedImage = document.querySelector('.displayed-img');
const thumbBar = document.querySelector('.thumb-bar');

const btn = document.querySelector('button');
const overlay = document.querySelector('.overlay');

/* Declaring the array of image filenames */
const files = ['pic11.jpg', 'pic22.jpg', 'pic33.jpg', 'pic44.jpg', 'pic55.jpeg'];

/* Declaring the alternative text for each image file */
const altText = {
    'pic11.jpg': 'tiger',
    'pic22.jpg': 'tiger',
    'pic33.jpg': 'tiger',
    'pic44.jpg': 'tiger',
    'pic55.jpg': 'tiger'
  };

/* Looping through images */

files.forEach((image) => {
    const newImage = document.createElement('img');
    newImage.setAttribute('src', `images/${image}`);
    newImage.setAttribute('alt', altText[image]);
    thumbBar.appendChild(newImage)

    newImage.addEventListener('click', () => {
        displayedImage.setAttribute('src', `images/${image}`);
        displayedImage.setAttribute('alt', altText[image]);
      });
    });

/* Wiring up the Darken/Lighten button */

btn.addEventListener('click', () => {
    const isDark = btn.getAttribute('class') === 'dark';
    if (isDark) {
      btn.setAttribute('class', 'light');
      btn.textContent = 'Lighten';
      overlay.style.backgroundColor = 'rgba(0, 0, 0, 0.5)';
    } else {
      btn.setAttribute('class', 'dark');
      btn.textContent = 'Darken';
      overlay.style.backgroundColor = 'rgba(0, 0, 0, 0)';
    }
  });
