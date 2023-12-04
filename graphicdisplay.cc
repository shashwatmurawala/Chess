 #include "graphicdisplay.h"

 GraphicDisplay::GraphicDisplay (GameManager &game, int width, int height):
    game{game}, win{(width + 2) * 20, (height + 2) * 20}, width{width + 1}, height{height + 1} {}

// one "block" is a 10x10 pixel square
 void GraphicDisplay::display() {
    win.drawString(30, 10, "a");
    win.drawString(50, 10, "b");
    win.drawString(70, 10, "c");
    win.drawString(90, 10, "d");
    win.drawString(110, 10, "e");
    win.drawString(130, 10, "f");
    win.drawString(150, 10, "g");
    win.drawString(170, 10, "h");
    win.drawString(7, 30, "1");
    win.drawString(7, 50, "2");
    win.drawString(7, 70, "3");
    win.drawString(7, 90, "4");
    win.drawString(7, 110, "5");
    win.drawString(7, 130, "6");
    win.drawString(7, 150, "7");
    win.drawString(7, 170, "8");
    for (int i = 1; i < height; i++) {
    	for (int j = 1; j < width; j++) {
         int row = j * 20;
         int col = i * 20;
         char tile = game.getTile(j - 1, i - 1);
         if ((i + j) % 2 == 0) {
            win.fillRectangle(row, col, 20, 20, 8);
         }
         else {
            win.fillRectangle(row, col, 20, 20, 9);
         }
         if (tile != ' ' && tile != '_') {
            std::string s {tile};
            win.drawString(row + 7, col + 15, s);
         }
	   }
   }
}
