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

<img width="1920" height="1003" alt="Screenshot (1058)" src="https://github.com/user-attachments/assets/11d62975-cc88-4f0f-8f58-db871bf58c96" />
<img width="1905" height="1012" alt="Screenshot (1059)" src="https://github.com/user-attachments/assets/36347bb3-528b-4b4d-80d9-0f43479bb062" />
<img width="1914" height="1013" alt="Screenshot (1061)" src="https://github.com/user-attachments/assets/ea1d272c-712f-4866-a286-228234e22b82" />


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


