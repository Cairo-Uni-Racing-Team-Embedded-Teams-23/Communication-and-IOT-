from numpy import asarray
from search import SimulatedAnnealing
from logger import setup_logger
from typing import List
import argparse

"""
A script which calculates the CAN bit timings according to given
inputs:

    Mandatory arguments:
        --baudrate  specifies the desired CAN baudrate in bits per second
        --pclk      specifies the APB clock in Hz

    Optional arguments:
        -i          iterations to perform during search
        -t          initial temperature for the search
        -s          the seed used for the search
        --debug     debug mode and debug logs

It will output the following:

    - Baudrate prescaler
    - Time segment 1
    - Time segment 2

usage: get_can_timings.py [-h] [-d] --baudrate BAUDRATE --pclk PCLK [-i ITERATIONS] [-t TEMPERATURE] [-s SEED]

example: get_can_timings.py --baudrate 250_000 --pclk 36_000_000

Author: Hazem Montasser
Date: July 12, 2023
"""

# Rest of the module code goes here...

ERROR_THRESHOLD: float = 0.0001
PCLK: int = 0
BAUDRATE: int = 0


def get_baudrate_difference(input: List[int]):
    """
    Calculate the difference between the baud rate obtained from the given input values and the predefined BAUDRATE.

    Args:
        input (List[int]): A list of three integers representing the values for input[0], input[1], and input[2]
        corresponding to TS1, TS2, and BRP values.

    Returns:
        float: The absolute difference between the calculated baud rate and the predefined BAUDRATE.
    """
    t_q = (input[2] + 1) * (1.0 / PCLK)
    t_bs1 = t_q * (input[0] + 1)
    t_bs2 = t_q * (input[1] + 1)
    bdr = 1.0 / (t_q + t_bs1 + t_bs2)
    return abs(bdr - BAUDRATE)


parser = argparse.ArgumentParser()
parser.add_argument("-d", "--debug", help="Debug level", action="store_true")
parser.add_argument("--baudrate", type=int, required=True, help="The goal baudrate.")
parser.add_argument(
    "--pclk", type=int, required=True, help="APB clock for the CAN peripheral."
)
parser.add_argument(
    "-i", "--iterations", type=int, default=10000, help="Iteration counts (optional)"
)
parser.add_argument(
    "-t", "--temperature", default=10, help="Initial temperature (optional)"
)
parser.add_argument(
    "-s", "--seed", type=str, help="The seed used for the search (optional)."
)
args = parser.parse_args()
debug_level = args.debug
iteration_counts = args.iterations
initial_temperature = args.temperature

# Set up the logger
logger = setup_logger(log_level=debug_level)

seed = args.seed
PCLK = args.pclk
BAUDRATE = args.baudrate

print(f"Starting simulated annealing to obtain CAN bit timings...")
print(f"Parameters: Goal baudrate = {BAUDRATE:,} bps, PCLK = {PCLK:,} Hz")

bounds = asarray([[0, 15], [0, 8], [0, 1024]])  # TS1  # TS2  # BRP
step_size = 1

s = SimulatedAnnealing(
    objective_function=get_baudrate_difference,
    bounds=bounds,
    step_size=step_size,
    iterations=iteration_counts,
    temperature=initial_temperature,
    debug=debug_level,
)

best, score, scores = s.search(seed)

print("f(%s) = %f" % (best, score))
print(f"BRP = {best[2]}, set baudrate prescaler to {best[2]+1}")
print(f"TS1 = {best[0]}, set time segment 1 to {best[0]+1}")
print(f"TS2 = {best[1]}, set time segment 2 to {best[1]+1}")

if score > ERROR_THRESHOLD:
    print(
        f"Error is {score}, greater than the error threshold {ERROR_THRESHOLD}. It is NOT recommended to use this value."
    )
    print("Try increasing the iterations for better results.")
