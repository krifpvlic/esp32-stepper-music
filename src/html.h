const char PAGE_MAIN[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
    <title>Stepper Music</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #242424
        }

        header {
            background-color: #242424;
            color: #fff;
            padding: 20px;
        }

        h1 {
            margin: 0;
        }

        main {
            padding: 20px;
        }

        .button-container {
            display: flex;
            justify-content: center;
            align-items: center;
            flex-wrap: wrap;
        }

        button {
            background-color: #007bff;
            color: #fff;
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            margin: 10px;
            cursor: pointer;
        }

        button:hover {
            background-color: #0069d9;
        }

        footer {
            background-color: #242424;
            color: #fff;
            text-align: center;
            padding: 10px;
        }

        /* CSS for the piano */

        .wrapper {
            padding: 35px 40px;
            border-radius: 20px;
            background: #141414;
        }

        .piano-keys {
            display: flex;
            list-style: none;
            margin-top: 40px;
        }

        .piano-keys .key {
            cursor: pointer;
            user-select: none;
            position: relative;
            text-transform: uppercase;
        }

        .piano-keys .black {
            z-index: 2;
            width: 44px;
            height: 140px;
            margin: 0 -22px 0 -22px;
            border-radius: 0 0 5px 5px;
            background: linear-gradient(#333, #000);
        }

        .piano-keys .black.active {
            box-shadow: inset -5px -10px 10px rgba(255, 255, 255, 0.1);
            background: linear-gradient(to bottom, #000, #434343);
        }

        .piano-keys .white {
            height: 230px;
            width: 70px;
            border-radius: 8px;
            border: 1px solid #000;
            background: linear-gradient(#fff 96%, #eee 4%);
        }

        .piano-keys .white.active {
            box-shadow: inset -5px 5px 20px rgba(0, 0, 0, 0.2);
            background: linear-gradient(to bottom, #fff 0%, #eee 100%);
        }

        .piano-keys .key span {
            position: absolute;
            bottom: 20px;
            width: 100%;
            color: #A2A2A2;
            font-size: 1.13rem;
            text-align: center;
        }

        .piano-keys .key.hide span {
            display: none;
        }

        .piano-keys .black span {
            bottom: 13px;
            color: #888888;
        }

        @media screen and (max-width: 815px) {
            .wrapper {
                padding: 25px;
            }

            header {
                flex-direction: column;
            }

            header :where(h2, .column) {
                margin-bottom: 13px;
            }

            .volume-slider input {
                max-width: 100px;
            }

            .piano-keys {
                margin-top: 20px;
            }

            .piano-keys .key:where(:nth-child(9), :nth-child(10)) {
                display: none;
            }

            .piano-keys .black {
                height: 100px;
                width: 40px;
                margin: 0 -20px 0 -20px;
            }

            .piano-keys .white {
                height: 180px;
                width: 60px;
            }
        }

        @media screen and (max-width: 615px) {

            .piano-keys .key:nth-child(13),
            .piano-keys .key:nth-child(14),
            .piano-keys .key:nth-child(15),
            .piano-keys .key:nth-child(16),
            .piano-keys .key :nth-child(17) {
                display: none;
            }

            .piano-keys .white {
                width: 50px;
            }
        }
    </style>
</head>

<body>
    <header>
        <h1>Stepper Music</h1>
    </header>
    <main>
        <div class="button-container">
            <button id="play-btn">Play a Song</button>
            <button id="keyboard-btn">Keyboard</button>
            <button id="stop-btn">Stop Playing</button>
            <button id="info-btn">Info</button>
        </div>
        <div id="content-container">
            <div id="song-list" style="display: none;">
                <h2>Songs</h2>
                <ul>
                    <li>Song 1</li>
                    <li>Song 2</li>
                    <li>Song 3</li>
                </ul>
            </div>
            <div id="keyboard" style="display: none;">
                <div class="wrapper">

                    <ul class="piano-keys">
                        <li class="key white" data-key="c"><span>c</span></li>
                        <li class="key black" data-key="c#"><span>c#</span></li>
                        <li class="key white" data-key="d"><span>d</span></li>
                        <li class="key black" data-key="d#"><span>d#</span></li>
                        <li class="key white" data-key="e"><span>e</span></li>
                        <li class="key white" data-key="f"><span>f</span></li>
                        <li class="key black" data-key="f#"><span>f#</span></li>
                        <li class="key white" data-key="g"><span>g</span></li>
                        <li class="key black" data-key="g#"><span>g#</span></li>
                        <li class="key white" data-key="a"><span>a</span></li>
                        <li class="key black" data-key="a#"><span>a#</span></li>
                        <li class="key white" data-key="b"><span>b</span></li>
                        <li class="key white" data-key="c"><span>c</span></li>
                        <li class="key black" data-key="c#"><span>c#</span></li>
                        <li class="key white" data-key="d"><span>d</span></li>
                        <li class="key black" data-key="d#"><span>d#</span></li>
                        <li class="key white" data-key="e"><span>e</span></li>
                    </ul>
                </div>

            </div>
            <div id="info" style="display: none;">
                <h2>Project Information</h2>
                <p>This project is a simple music player and keyboard application built with HTML, CSS, and JavaScript.
                    It allows users to play songs and experiment with a virtual keyboard. The code for this project is
                    easily modifiable and can be adapted to fit a variety of use cases.</p>
            </div>
        </div>
    </main>
    <footer>
        <p>MIT Licence</p>
    </footer>
    <script>
        const playBtn = document.getElementById("play-btn");
        const songList = document.getElementById("song-list");
        const keyboardBtn = document.getElementById("keyboard-btn");
        const keyboard = document.getElementById("keyboard");
        const stopBtn = document.getElementById("stop-btn");
        const infoBtn = document.getElementById("info-btn");
        const info = document.getElementById("info");
        const piano = document.getElementById("piano");
        const contentContainer = document.getElementById("content-container");


        playBtn.addEventListener("click", () => {
            info.style.display = "none";
            keyboard.style.display = "none";
            songList.style.display = "block";
        });

        keyboardBtn.addEventListener("click", () => {
            info.style.display = "none";
            songList.style.display = "none";
            keyboard.style.display = "block";
        });

        stopBtn.addEventListener("click", () => {
            // code to stop playing
        });

        infoBtn.addEventListener("click", () => {
            keyboard.style.display = "none";
            songList.style.display = "none";
            info.style.display = "block";
        });

        const whiteKeys = document.querySelectorAll(".white");
        const blackKeys = document.querySelectorAll(".black");
        const noteMap = {
            C: "C4",
            "C#": "C#4",
            D: "D4",
            "D#": "D#4",
            E: "E4",
            F: "F4",
            "F#": "F#4",
            G: "G4",
            "G#": "G#4",
            A: "A4",
            "A#": "A#4",
            B: "B4"
        };

        function playNote(note) {
            const audio = new Audio(`notes/${note}.mp3`);
            audio.play();
        }

        function handleClick(e) {
            const note = e.target.dataset.note;
            playNote(noteMap[note]);
        }

        whiteKeys.forEach(key => {
            key.addEventListener("mousedown", handleClick);
        });

        blackKeys.forEach(key => {
            key.addEventListener("mousedown", handleClick);
        });
    </script>
</body>

</html>
)=====";