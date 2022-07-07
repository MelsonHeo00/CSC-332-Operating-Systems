import java.util.Scanner;  // Scanner Class (user input)

public class Assignment2 {

    /**
     * main class of this assignment for when there is one thread
     * @param args
     * @throws Exception
     */

    public static void main(String[] args) throws Exception{

        // number of threads
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter how many threads you would like: ");
        // letters will give you an error

        // converts scanner to int
        int threads = scan.nextInt();
        scan.close();

        // factorize number
        Factorize[]factor = new Factorize[threads];

        // timer starts
        long start = System.currentTimeMillis();

        // for loop for the thread task and factorizing
        for(int i = 0; i < threads; i++){

            // assigning each thread task
            factor[i] = new Factorize(i * 10000/threads, (i + 1) * 10000 / threads);
            factor[i].start();
        }

        // joining the threads
        for(int i = 0; i < threads; i++) {
            factor[i].join();
        }

        // timer stops
        long end = System.currentTimeMillis();

        int result = -1;
        int maxFactor = 0;

        // max results
        for(int i = 0; i < threads; i++){
            if(factor[i].maxFactor > maxFactor){
                maxFactor = factor[i].maxFactor;
                result = factor[i].result;
            }
        }

        // the time difference
        long time = end - start;

        System.out.println("-------------------------------------------------");
        System.out.println("Largest Number of Factors");
        System.out.println("Number between 1 and 10000: " + result);
        System.out.println("These are the number of factors: " + maxFactor);
        System.out.println("-------------------------------------------------");
        System.out.println("Threads");
        System.out.println("Number of Threads: " + threads);
        System.out.println("Time (in ms): " + time);
    }
}

/**
 * class that factorizes the minimum to maximum range
 */

class Factorize extends Thread{

    // int declaration of minimum, maximum, the result of the number, and maximum of the factor
    int lower, upper, result, maxFactor;

    //range of the numbers to find solution
    Factorize(int l, int u){
        lower = l ;
        upper = u ;
        maxFactor = 0;
    }

    // factor of 1 number
    int numOfFactor(int number){
        int count = 0;
        for(int i = 1; (i) <= number; i++) {
            if (number % i == 0) {
                count++;
            }
        }
        return count;
    }

    // running the numbers
    @Override
    public void run() {
        for(int i = lower; i <= upper; i++) {
            int f = numOfFactor(i);
            if(f > maxFactor){
                maxFactor = f;
                result = i;
            }
        }
    }

}