// Define an object containing information about songs
const songs = {
    lonelyrariTeamrocket: {
        id: "lonelyrari-teamrocket",
        title: "Team Rocket",
        artist: "lonelyrari",
        songSrc: "./songs/lonelyrari - team rocket.mp3",
        imageSrc: "./album-images/lonelyrari - team rocket.jpg" 
    },
    miguelSurething: {
        id: "miguel-surething", 
        title: "Sure Thing", 
        artist: "Miguel", 
        songSrc: "./songs/miguel - sure thing.mp3",
        imageSrc: "./album-images/miguel - sure thing.jpg"
    },
    ethanrossAngeldust: {
        id: "ethanross-angeldust", 
        title: "Angel Dust", 
        artist: "Ethan Ross", 
        songSrc: "./songs/ethan ross - angel dust.mp3",
        imageSrc: "./album-images/ethan ross - angel dust.jpg"
    },
    guccimaneWakeupinthesky: {
        id: "guccimane-wakeupinthesky", 
        title: "Wake Up In The Sky", 
        artist: "Gucci Mane, Bruno Mars, Kodak Black", 
        songSrc: "./songs/gucci mane, bruno mars, kodak black - wake up in the sky.mp3",
        imageSrc: "./album-images/gucci mane, bruno mars, kodak black - wake up in the sky.jpg"
    },
}   

// Get DOM elements
const songTimeBar = document.getElementById("song-timebar");
const audio = new Audio('');
const dropdown = document.getElementById('dropdown');
const songVolume = document.getElementById('song-volume');
const volume = document.getElementById('volume');

// Set initial volume
audio.volume = volume.value / 100;
let lastVolume = audio.volume;
let repeat;

// Remove event listeners for audio
function removeAudioEventListeners() {
    audio.removeEventListener('timeupdate', UpdateTrackInfo);
    audio.removeEventListener('loadedmetadata', UpdateTrackInfo);
}

// Load and play a song
function LoadAndPlaySong(song) {
    const { id, title, artist, songSrc, imageSrc } = song;

    if (id) {
        // Update song information
        let songImage = document.getElementById("song-image");
        let songTitle = document.getElementById("song-title");
        let songArtist = document.getElementById("song-artist");  
        
        songTitle.innerHTML = title;
        songArtist.innerHTML = artist;
        audio.src = songSrc;
        songImage.src = imageSrc;
        songTimeBar.style.setProperty('--track-width', '0%');
        DisableRepeat();
        ContinuePlayer();
    
        // Update active song
        let currentSong = document.querySelector(".song.active");  
        if (currentSong) {
            currentSong.classList.remove("active");
        }
        
        let newSong = document.getElementById(id);
        if (newSong) {
            newSong.classList.add("active");
        }
    
        removeAudioEventListeners();
        audio.addEventListener('timeupdate', function() {
            UpdateTrackInfo(audio);
        });
    
        audio.addEventListener('loadedmetadata', function() {
            UpdateTrackInfo(audio);
        });
    } else {
        console.error("Song not found!");
    }
}

// Update track information
function UpdateTrackInfo() {
    UpdateTrackTime(audio);
    UpdateTrackBar(audio);
}

// Update track time display
function UpdateTrackTime(track) {
    let currTimeDiv = document.getElementById("time-left");
    let durationDiv = document.getElementById("time-total");

    currTimeDiv.innerHTML = formatSecondsAsTime(Math.floor(track.currentTime));

    if (isNaN(track.duration) || track.duration < 0) {
        durationDiv.innerHTML = "00:00";
    } else {
        durationDiv.innerHTML = formatSecondsAsTime(Math.floor(track.duration));
    }
}

// Update track progress bar
function UpdateTrackBar(track) {
    songTimeBar.style.setProperty('--track-width', `${(track.currentTime / track.duration) * 100}%`);
}

// Format seconds as time (mm:ss)
function formatSecondsAsTime(seconds) {
    let minutes = Math.floor(seconds / 60);
    let secs = seconds % 60;
    if (secs < 10) secs = "0" + secs;
    return minutes + ":" + secs;
}

// Handle song button click
function HandleSongButtonClick(song) {
    LoadAndPlaySong(song);
}

// Handle skip button click
function HandleSkipButtonClick() {
    let currentSong = document.querySelector(".song.active");
    if (currentSong) {
        let nextSong = GetNextSong(currentSong);
        if (nextSong) {
            LoadAndPlaySong(songs[nextSong]);
        }
    } else {
        let nextSong = FindSongByID(document.querySelector(".songs").firstElementChild.id);
        if (nextSong) {
            LoadAndPlaySong(songs[nextSong]);
        } else {
            console.error("No songs available!");
        }
    }
}

// Handle previous button click
function HandlePreviousButtonClick() {
    if (audio.currentTime > 1) {
        audio.currentTime = 0;
    } else {
        let currentSong = document.querySelector(".song.active");
        if (currentSong) {
            let previousSong = GetPreviousSong(currentSong);
            LoadAndPlaySong(songs[previousSong]);
        } else {
            let previousSong = FindSongByID(document.querySelector(".songs").lastElementChild.id);
            LoadAndPlaySong(songs[previousSong]);
        }
    }
}

// Handle play/pause button click
function HandlePlayPauseButton() {
    let ppButton = document.getElementById("play-pause-button");
    if (ppButton.classList.contains("playing")) {
        PausePlayer();
    } else {
        ContinuePlayer();
    }
}

// Handle repeat button click
function HandleRepeatButton() {
    let repeatButton = document.getElementById("repeat");
    if (repeatButton.classList.contains("repeat-off")) {
        EnableRepeat();
    } else {
        DisableRepeat();
    }
}

// Disable repeat mode
function DisableRepeat() {
    let repeatButton = document.getElementById("repeat");
    repeatButton.classList.replace("repeat-on", "repeat-off");
    repeat = false;

    audio.removeEventListener("ended", RepeatHandler);
}

// Enable repeat mode
function EnableRepeat() {
    let repeatButton = document.getElementById("repeat");
    repeatButton.classList.replace("repeat-off", "repeat-on");
    repeat = true;

    audio.addEventListener("ended", RepeatHandler);
}

// Repeat the song when it ends
function RepeatHandler() {
    this.currentTime = 0;
    this.play();
}

// Show volume control
function ShowVolume() {
    volume.style.display = "inline";
}

// Hide volume control
function HideVolume() {
    volume.style.display ="none";
}

// Handle volume button click
function HandleVolumeButton() {
    if (songVolume.classList.contains("muted")) {
        Unmute();
    } else {
        Mute();
    }
}

// Mute the audio
function Mute() {
    songVolume.classList.add("muted");
    lastVolume = audio.volume
    audio.volume = 0;
}

// Unmute the audio
function Unmute() {
    songVolume.classList.remove("muted");
    audio.volume = lastVolume
}

// Change song time based on click position
function ChangeTime(e) {
    let xPosition = e.clientX;
    let BarLeft = songTimeBar.getBoundingClientRect().left;
    let xRelativeToBar = xPosition - BarLeft;
    console.log(xRelativeToBar);
    let barWidth = songTimeBar.offsetWidth;

    audio.currentTime = (audio.duration / barWidth) * xRelativeToBar;
}

// Change volume based on input value
function ChangeVolume(value) {
    audio.volume = value / 100;
}

// Pause the audio player
function PausePlayer() {
    let ppButton = document.getElementById("play-pause-button");
    ppButton.classList.replace("playing", "paused");
    audio.pause();
}

// Continue playing the audio player
function ContinuePlayer() {
    let ppButton = document.getElementById("play-pause-button");
    ppButton.classList.replace("paused", "playing");
    audio.play();
}

// Get the next song
function GetNextSong(currentSong) {
    let nextSong = currentSong.nextElementSibling || currentSong.parentNode.firstElementChild;
    currentSong.classList.remove("active");
    nextSong.classList.add("active")
    return FindSongByID(nextSong.id);
}

// Get the previous song
function GetPreviousSong(currentSong) {
    let nextSong = currentSong.previousElementSibling || currentSong.parentNode.lastElementChild;
    currentSong.classList.remove("active");
    nextSong.classList.add("active");
    return FindSongByID(nextSong.id);
}

// Find a song by its ID
function FindSongByID(id) {
    for (const [key, song] of Object.entries(songs)) {
        if (Object.values(song).includes(id)) {
            return key;
        }
    }
}

// Add event listeners to song buttons
document.getElementById("lonelyrari-teamrocket").addEventListener("click", function() {
    HandleSongButtonClick(songs.lonelyrariTeamrocket);
});

document.getElementById("miguel-surething").addEventListener("click", function() {
    HandleSongButtonClick(songs.miguelSurething);
});

document.getElementById("ethanross-angeldust").addEventListener("click", function() {
    HandleSongButtonClick(songs.ethanrossAngeldust);
});

document.getElementById("guccimane-wakeupinthesky").addEventListener("click", function() {
    HandleSongButtonClick(songs.guccimaneWakeupinthesky);
});

// Add event listeners to control buttons
document.getElementById("skip-button").addEventListener("click", function() {
    HandleSkipButtonClick();
});

document.getElementById("previous-button").addEventListener("click", function() {
    HandlePreviousButtonClick();
});

document.getElementById("play-pause-button").addEventListener("click", function() {
    HandlePlayPauseButton();
});

document.getElementById("repeat").addEventListener("click", function() {
    HandleRepeatButton();
});

// Add event listener for song end
audio.addEventListener("ended", function() {
    if (!repeat) {
        PausePlayer();
        HandleSkipButtonClick();
    } 
});

// Add event listeners for volume control
songVolume.addEventListener("click", function() {
    HandleVolumeButton();
});

volume.addEventListener("mousedown", Unmute, false);

volume.addEventListener("input", function() {
    ChangeVolume(this.value);
}, false);

dropdown.addEventListener("mouseenter", ShowVolume);
songVolume.addEventListener("mouseenter", ShowVolume);
volume.addEventListener("mouseenter", ShowVolume);

dropdown.addEventListener("mouseleave", () => {
    setTimeout(() => {
        if (!volume.matches(":hover")) {
            HideVolume();
        }
    }, 100);
});

songVolume.addEventListener("mouseleave", () => {
    setTimeout(() => {
        if (!volume.matches(":hover")) {
            HideVolume();
        }
    }, 100);
});

// Add event listener for song time bar click
songTimeBar.addEventListener("click", ChangeTime, false);