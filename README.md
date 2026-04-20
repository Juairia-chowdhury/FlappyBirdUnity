# 🐦 Flappy Bird (OpenGL C++)

A simple **2D Flappy Bird game** built using **C++ and OpenGL (GLUT)**.
This project demonstrates basic computer graphics concepts like rendering, animation, collision detection, and interactive gameplay.

---

## 🎮 Features

* 🐤 Smooth bird movement with gravity physics
* 🧱 Moving pipes with collision detection
* 🌤️ Beautiful background (clouds, grass, flowers)
* 🌗 **Day/Night Mode with smooth transition**
* ☀️ Glowing Sun (day mode)
* 🌙 Moon & ⭐ stars (night mode)
* 🔄 Restart system
* 📊 Score tracking system

---

## 🌗 Day/Night System

* Press **N** to toggle between **Day ☀️ and Night 🌙**
* Smooth transition using color interpolation
* Clouds fade out at night
* Stars gradually appear
* Sun fades out, Moon fades in

---

## 🎮 Controls

| Key     | Action           |
| ------- | ---------------- |
| `SPACE` | Jump             |
| `N`     | Toggle Day/Night |
| `R`     | Restart Game     |

---

## 🛠️ Technologies Used

* **C++**
* **OpenGL**
* **GLUT (OpenGL Utility Toolkit)**

---

## 📸 Screenshots

*<img width="1920" height="1012" alt="Screenshot (1054)" src="https://github.com/user-attachments/assets/826ecbc1-61c6-4af8-a771-bdb01ef31be3" />
<img width="1909" height="1010" alt="Screenshot (1055)" src="https://github.com/user-attachments/assets/c094b1c2-f3a9-4bbb-a81a-8dffbde5b6e8" />
<img width="1920" height="1010" alt="Screenshot (1056)" src="https://github.com/user-attachments/assets/c131d6c3-24cc-41dd-a30a-edcac728be9c" /> *

---

## 🚀 How to Run

### 1. Install Requirements

Make sure you have:

* OpenGL
* GLUT / FreeGLUT

### 2. Compile

```bash
g++ flappy.cpp -o flappy -lglut -lGL -lGLU
```

### 3. Run

```bash
./flappy
```

---

## 📂 Project Structure

```
FlappyBird/
│── main.cpp
│── README.md
```

---

## 💡 Concepts Used

* 2D Rendering with OpenGL
* Game Loop using `glutTimerFunc`
* Collision Detection
* Animation & Physics (gravity, velocity)
* Linear Interpolation (LERP) for smooth transitions

---

## 🎯 Future Improvements

* 🌇 Sunset gradient effect
* 🌧 Rain system
* ✨ Twinkling stars animation
* 🔊 Sound effects
* 📱 Mobile-friendly version

---

## 👩‍💻 Author

**Your Name Here**

---

## ⭐ Support

If you like this project, give it a ⭐ on GitHub!

---
