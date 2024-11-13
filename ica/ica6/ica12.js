
const factParagraph = document.getElementById('fact');
const fetchButton = document.getElementById('fetchButton');
const apiEndpoint = 'https://catfact.ninja/fact';
fetchButton.addEventListener('click', getFact);

function getFact() {
  console.log('Loading...');

  fetch(apiEndpoint)
    .then(response => {
      if (!response.ok) {
        throw new Error('Error');
      }
      return response.json();
    })
    .then(data => {
      console.log(data.fact);
      displayRes(data.fact);
    })
    .catch(error => {
      console.error('Error fetching data:', error);
      alert('Failed.');
    });
}

function displayRes(fact) {
  factParagraph.textContent = fact;
}

getFact();
