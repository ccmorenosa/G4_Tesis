#!/bin/python3
"""
Train machine learning.

Script that take data from the root files and train a machine learning with
scikitlearn lib.
"""
from sklearn.naive_bayes import MultinomialNB
from sklearn.naive_bayes import BernoulliNB
from sklearn.linear_model import Perceptron
from sklearn.linear_model import SGDClassifier
from sklearn.linear_model import PassiveAggressiveClassifier
# from data_mng import root_files_mng
import root_files_mng
import pandas as pd
import numpy as np
import argparse

# Set parser for the console arguments.
parser = argparse.ArgumentParser(description='Train and machine learning.',
                                 formatter_class=argparse.RawTextHelpFormatter)

# Set arguments.
parser.add_argument("-tp", "--train_parameters", type=str,
                    metavar="params_file",
                    help="A csv file with the classifiers parameters.")

parser.add_argument("-tr", "--train", type=str, nargs="+",
                    metavar="train_file",
                    help="The input root file to train the machine learning.")

parser.add_argument("-ts", "--test", type=str, metavar="test_file", nargs="+",
                    required=True,
                    help="The input root file to test the machine learning.")

parser.add_argument("-c", "--classifier", type=str,
                    metavar="classifier_method", default="MultinomialNB",
                    help="""
The machine learning classifier to be used. You can select between
MultinomialNB, BernoulliNB, Perceptron, SGDClassifier and
PassiveAggressiveClassifier. (default: MultinomialNB).""")

# Parse arguments.
args = parser.parse_args()

classifiers_dict = {
    "MultinomialNB": MultinomialNB,
    "BernoulliNB": BernoulliNB,
    "Perceptron": Perceptron,
    "SGDClassifier": SGDClassifier,
    "PassiveAggressiveClassifier": PassiveAggressiveClassifier
}

# Create the classifiers.
print(f"\nUsing {args.classifier} classifier")
clf = classifiers_dict[args.classifier]()

# Get the test variables.
print("\nGet test set\n")
res_files = root_files_mng.get_data(args.test)

if args.train:
    # Train the data.
    print("\nTraining\n")
    root_files_mng.train_data(args.train, clf)
    print("\nTrained\n")
elif args.train_parameters:
    # Train the data.
    config_dict = pd.read_json(args.train_parameters).T.Config[args.classifier]
    print(f"\nConfigured\n{config_dict}\n")
    clf.set_params(config_dict)
    print("\nConfigured\n")

print("\nTest results: \n")

# The array for the scores result
test_scores = []
particle_scores = {
    0: [],
    1: [],
    2: [],
}

for res_file in res_files:
    test_scores, particle_scores = root_files_mng.test_res(
        clf, res_file, test_scores, particle_scores
    )

# Print results of the test.
print("\n")
print(f"Results:  {np.mean(test_scores)}")
print(f"Results gamma: {np.mean(particle_scores[0])}")
print(f"Results pi0: {np.mean(particle_scores[1])}")
print(f"Results electron: {np.mean(particle_scores[2])}")
# print(f"Config {clf.get_params()}\n\n")
