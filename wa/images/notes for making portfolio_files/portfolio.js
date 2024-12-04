fetch('../final/projects.json')
.then(response =>{
    return response.json();
}).then(projects => {
    console.log(projects);
    proj = projects;
    parseData(projects);
}).catch(err =>{
    console.log(`error ${err}`);
})

// first project - candyland / c++ part of portfolio
// div for each part of the json file + different displays 

function parseData(data){
    for(let i=0; i<data.projects.length; i++){
    document.getElementById("projects").innerHTML += `<a href = /final/${data.projects[i].subdomain}.html">
    <div class="row project" id="${data.projects[i].subdomain}">
    
        <div class="projimg"> <img src="https://aubrey888.github.io/images/chick.png"> </div>
        <div class="description"> <h2>${data.projects[i].name}</h2><p class="subtitle">${data.projects[i].subtitle}</p>
        <p>${data.projects[i].abstract}</p></div></div></a>`;
    }
}

for(b of document.querySelectorAll("#button button")) {
    b.addEventListener("click", e=> {
        console.log(e.target.value);
    })
}