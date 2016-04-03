/******************************************************************************
 *  Nome: Nicolas Nogueira Lopes da Silva
 *  Nº USP: 9277541
 *
 *  Compilacao: javac-algs4 paint.java
 *  Execucao: java-algs4 paint input.txt
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