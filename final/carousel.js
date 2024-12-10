const displayedImage = document.querySelector('.displayed-img');
const thumbBar = document.querySelector('.thumb-bar');

// Array of image filenames
const files = ['gallery1.png', 'gallery2.png', 'gallery3.png', 'gallery4.png'];

// Alternative text for each image
const altText = {
  'gallery1.png': 'Screenshot 1',
  'gallery2.png': 'Screenshot 2',
  'gallery3.png': 'Screenshot 3',
  'gallery4.png': 'Screenshot 4',
};

// Loop through images to add thumbnails
files.forEach((image) => {
  const newImage = document.createElement('img');
  newImage.setAttribute('src', `assets/${image}`);
  newImage.setAttribute('alt', altText[image]);
  thumbBar.appendChild(newImage);

  newImage.addEventListener('click', () => {
    displayedImage.setAttribute('src', `assets/${image}`);
    displayedImage.setAttribute('alt', altText[image]);
  });
});
