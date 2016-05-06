/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Compilacao: javac paint.java
 *  Execucao: java paint input.txt
 *  Dependencias: StdDraw.java

 *  Recebe da entrada padrao as coordenadas x e y e plota em uma simulacao
 *  grafica com uma animacao da movimentacao dos corpos.
 *
 *  % java-algs4 paint < input.txt
 *
 ******************************************************************************/
import java.awt.*;

public class paint{

    // test client
    public static void main(String[] args) {
    	// turn on animation mode and rescale coordinate system
    	Double radius = 1000.0;
        StdDraw.show(0);
        StdDraw.setXscale(-radius, +radius);
        StdDraw.setYscale(-radius, +radius);
        Color color = StdDraw.BLACK;
        while (!StdIn.isEmpty()) {
            // draw the bodies
        	StdDraw.clear(StdDraw.WHITE);
        	StdDraw.setPenColor(color);
        	StdDraw.circle(StdIn.readFloat(), StdIn.readFloat(), 2);
            StdDraw.circle(StdIn.readFloat(), StdIn.readFloat(), 2);
        	StdDraw.circle(StdIn.readFloat(), StdIn.readFloat(), 2);
        	StdDraw.show(1);
        }
        System.out.println("Acabou");
    }
}