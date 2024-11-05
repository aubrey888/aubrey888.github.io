// 1. complete & varaible functions
const customName = document.getElementById('customname');
const randomize = document.querySelector('.randomize');
const story = document.querySelector('.story');

function randomValueFromArray(array) {
  const random = Math.floor(Math.random() * array.length);
  return array[random];
}
// 2. raw text strings

const storyText =
  "It was cold outside, so :insertx: went for a walk. When they got to :inserty:, they stopped in their tracks, then :insertz:. Bob saw the whole thing, but was not surprised — :insertx: likes ice cream, and it was a chilly day.";

const insertX = ["Baylie", "Johnny Test", "The Grinch"];
const insertY = ["New York", "Paris", "Denver"];
const insertZ = [
  "burst into flames",
  "decided to order soup",
  "turned into a tiger",
];

randomize.addEventListener("click", result);
function result() {
  let newStory = storyText;

  const xItem = randomValueFromArray(insertX);
  const yItem = randomValueFromArray(insertY);
  const zItem = randomValueFromArray(insertZ);


  newStory = newStory.replaceAll(":insertx:", xItem);
  newStory = newStory.replace(":inserty:", yItem);
  newStory = newStory.replace(":insertz:", zItem);

  if (customName.value !== "") {
    const name = customName.value;
    newStory = newStory.replace("Bob", name);
  }


  // uk measurements
  if (document.getElementById("uk").checked) {
    const weight = Math.round(300 * 0.0714286) + " stone"; 
    const temperature = Math.round((94 - 32) * (5 / 9)) + " centigrade"; 

    newStory = newStory.replace("300 pounds", weight);
    newStory = newStory.replace("94 fahrenheit", temperature);
  }

  story.textContent = newStory;
  story.style.visibility = "visible";
}
