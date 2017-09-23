import argparse as arp
import numpy as np
import matplotlib.pyplot as plt

def main():
    parser = arp.ArgumentParser()
    parser.add_argument("fileName", help="Name of file containing data.")
    parser.add_argument("-x", "--xAxisName", help="x axis name string")
    parser.add_argument("-y", "--yAxisName", help="y axis name string")
    parser.add_argument("-t", "--title", help="chart title")
    args = parser.parse_args()

    # Parse input file
    # We're expecting each input file to be lines consisting of three key-value pairs.
    # A key-value pair consists of a string (key) which is largely ignored,
    # and a value. An '=' seperates the key from the value.
    # Each key-value pair is seperated by a space. For example...
    # TIME=0.012 unfilteredVelocity=0.00013189 filteredVelocity=0.00013190
    time = []
    measured = []
    filtered = []
    yaxis = ["", ""]
    with open(args.fileName, 'r') as f:
            for line in f:
                    spl = line.rstrip().split()                             # Split by spaces.
                    time.append(float(spl[0].split('=')[1]))                # split by '=', take 2nd
                    measured.append(float(spl[1].split('=')[1]))
                    filtered.append(float(spl[2].split('=')[1]))
    # She's in ram, boss!
    fig = plt.figure()
    fig.suptitle(args.title, fontsize=13, fontweight='bold')
    ax = fig.add_subplot(111)
    ax.set_xlabel(args.xAxisName)
    ax.set_ylabel(args.yAxisName)

    ax.plot(time, measured, '-bo', time, filtered, '-ro')
    plt.show()

if __name__ == "__main__":
        main()