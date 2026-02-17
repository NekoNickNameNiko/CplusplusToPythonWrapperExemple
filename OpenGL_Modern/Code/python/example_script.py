# exemple de script Python pour test avec PyUtility::Print
# ------------------
# Fonctions
# ------------------
import engine # Py module for engine interaction

def greet():
    print("Hello from Python!")

def add(a, b):
    print(a + b)

def update_camera(camera : engine.Camera, Direction : engine.Vector3):
    camera.move(Direction)

def Print():
    print(dir(engine))

a = 0
b = 0

def Update(deltatime: float = 0):
    global a
    a += 1

def FixedUpdate(deltatime: float = 0):
    global b
    b += 1
    print(a)

# ------------------
# Classes
# ------------------
class Player:
    def __init__(self, name):
        self.name = name
    
    def say_name(self):
        print(f"My name is {self.name}")

class Enemy:
    def __init__(self, level):
        self.level = level
    
    def attack(self):
        print(f"Enemy attacks with level {self.level}")
