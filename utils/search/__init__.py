from typing import Callable, Optional
from numpy import exp
from numpy.random import rand
from numpy.random import seed
from numpy.random import MT19937
from numpy.random import RandomState, SeedSequence
import numpy as np
from logger import setup_logger


class LocalSearch:
    def __init__(self, objective_function: Callable, **kwargs):
        self.objective_function = objective_function
        self.kwargs = kwargs
        pass

    def search(self, _seed=None):
        pass


class SimulatedAnnealing(LocalSearch):
    def __init__(
        self,
        objective_function: Callable,
        bounds: np.ndarray,
        step_size: float = 1,
        iterations: int = 100,
        temperature: float = 1.0,
        **kwargs,
    ):
        super().__init__(objective_function=objective_function)
        self.bounds = bounds
        self.step_size = step_size
        self.iterations = iterations
        self.temperature = temperature
        self.kwargs = kwargs
        # Set up the logger
        self.logger = setup_logger(log_level=kwargs.get("debug", False))
        self.logger.debug("Simulated Annealing initialized")
        self.logger.debug(f"Step size: {self.step_size}")
        self.logger.debug(f"Iterations: {self.iterations}")
        self.logger.debug(f"Temperature: {self.temperature}")
        self.logger.debug(f"Bounds: {self.bounds}")
        self.logger.debug(f"kwargs: {self.kwargs}")
        return

    def search(self, _seed: Optional[int] = None):
        """
        Perform a search algorithm to find the best solution for the given objective function.

        Parameters:
            _seed (optional): A seed value to ensure reproducibility of the search algorithm.

        Returns:
            list: A list containing the best solution found, the evaluation value of the best solution,
            and a list of scores at each iteration.
        """
        if _seed is not None:
            self.logger.debug(f"Seed: {_seed}")
            seed(_seed)
        else:
            self.logger.debug("No seed provided")
            # Generate a new seed for this run if none was provided
            rs = RandomState(MT19937(SeedSequence(123456789)))

        step_size = self.step_size
        bounds = self.bounds
        objective = self.objective_function

        # Generate an initial point
        best = np.random.randint(bounds[:, 0], bounds[:, 1] + 1)
        # Evaluate the initial point
        best_eval = objective(best)
        # Current working solution
        curr, curr_eval = best, best_eval
        scores = list()

        # Run the algorithm
        for i in range(self.iterations):
            # Get the next point
            candidate = np.random.randint(bounds[:, 0], bounds[:, 1] + 1)
            # Calculate the objective function for this point
            candidate_eval = objective(candidate)
            # Check for new best solution
            if candidate_eval < best_eval:
                # Set as new best
                best, best_eval = candidate, candidate_eval
                # Save to scores
                scores.append(best_eval)
                self.logger.debug(">%d f(%s) = %.5f" % (i, best, best_eval))
            # Calculate the difference between candidate point and current point
            diff = candidate_eval - curr_eval
            # Schedule the new temperature for the current time
            t = self.temperature / float(i + 1)
            # Calculate the probability
            metropolis = exp(-diff / t)
            # Check if we should keep the new point
            if diff < 0 or rand() < metropolis:
                # Store the new current point
                curr, curr_eval = candidate, candidate_eval
        return [best, best_eval, scores]
