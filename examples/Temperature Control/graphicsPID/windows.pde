class Windows {
  
  private float x, y, _height, _width;
  private int backGround;

  // Construtor
  Windows(float x, float y, float _width, float _height){
    this.x = x;
    this.y = y;
    this._height = _height;
    this._width = _width;
    backGround = 255;     // default

  }
  
  // Construtor
  Windows(float x, float y, float _width, float _height, int backGround){
    this.x = x;
    this.y = y;
    this._height = _height;
    this._width = _width;
    this.backGround = backGround;
  }  
  
  // Criar Janela com texto no canto superior esquerdo
  public void createWindow(String text){
    stroke(0);
    fill(backGround);
    rect(x, y, _width, _height);
    fill(0);
    textSize(18);
    text(text, x+2, y+18);
  }
  
  public void createWindow(String text, int textSize){
    stroke(0);
    fill(backGround);
    rect(x, y, _width, _height);
    fill(0);
    textSize(textSize);
    text(text, x+2, y+textSize);
  }
  
  public void createText(String string, int x, int y, int textSize){
    fill(0);
    textSize(textSize);
    text(string, this.x + x, this.y + y + textSize);     
  }
}