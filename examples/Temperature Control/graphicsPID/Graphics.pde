class Graphic { 

  private float x, y, _height, _width;  // dimensões da janela
  private int[] samples;                // conjunto de amostras
  private int nSamples;                 // quantidade de amostras
  private int sample;                   // amostra mais atual 
  private int cor;
  private static final float division = 1;
  
  private int MAX;
  private int MIN;

  public Graphic(Windows window, int cor, int min, int max) {
    this.x = window.x;
    this.y = window.y;
    this._height = window._height;
    this._width = window._width;

    nSamples = (int)(_width/division);    // número de amostras = largura/divisões
    samples = new int[nSamples];

    MAX = max;
    MIN = min;
    this.cor = cor;
  }
  
  public int getSample() {
    return sample;
  }

  public void addNewSample(int newSample) {

    // Deslocar os valores existentes para liberar espaço para novos valores.
    for (int i = 0; i < nSamples-1; i++)
      samples[i] = samples[i + 1];

    // Inclua ao vetor (na última posição) o valor recebido
    samples[nSamples-1] = (int)map(newSample, MIN, MAX, 0, _height);
    sample = newSample;             // valor mais novo
  }

  public void drawGraphic() {
    pushMatrix();
      translate(x, y);
      stroke(cor);
      for (int i = 0; i < nSamples-1; i++)
        line(i * division, _height - samples[i], (i + 1) * division, _height - samples[i + 1]);
    popMatrix();
  }
}