/* *****************************************************************************
 *  Name:    Daphne Barretto
 *  NetID:   daphnegb
 *  Precept: P09
 *
 *  Description:  This parses rocket data.
 *
 **************************************************************************** */

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class Parser {

    public static void main(String[] args) {

        String filename = args[0];
        In in = new In(filename);

        double firstAlt = 0.0;

        StdOut.println("Altitude(ft),Pressure(Pa),Temperature(f)");

        while (in.hasNextLine()) {
            String line = in.readLine();
            String[] lineArr = line.split("[: ]");

            if (!lineArr[0].equals(""))
                continue;

            if (lineArr.length > 6) {
                double altitude = Double.parseDouble(lineArr[2]);
                double pressure = Double.parseDouble(lineArr[4]);
                double temp = Double.parseDouble(lineArr[6]);

                if (firstAlt == 0.0)
                    firstAlt = altitude;

                StdOut.println((altitude - firstAlt) + "," + pressure + "," + temp);
            }

        }

    }

}
