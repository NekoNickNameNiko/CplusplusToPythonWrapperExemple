# exemple de script Python pour test avec PyUtility::Print
# ------------------
# Fonctions
# ------------------
def greet():
    print("Hello from Python!")

def add(a, b):
    return a + b

def update_camera(camera):
    # exemple d'appel sur un objet C++ passé
    camera.move(1.0, 0.0, 0.0)
    print("Camera updated by Python")

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
