import sys
from PyQt6.QtWidgets import QWidget, QLineEdit, QApplication
 
class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.resize(250, 200)
        self.setWindowTitle("CodersLegacy")
 
        input = QLineEdit(self)
        input.editingFinished.connect(self.handleInput)
        input.move(60, 60)
 
        input2 = QLineEdit(self)
        input2.move(60, 100)
 
        self.show()
 
    def handleInput(self):
        print("Input Finished")
        print("Submitting Input....")
 
app = QApplication(sys.argv)
window = Window()
sys.exit(app.exec())