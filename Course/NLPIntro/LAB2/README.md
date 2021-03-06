# Evaluation Criteria

Note: Evaluations on Test Set will happen during Jan 10-31, 2020 according to SemEval rules.

## Sub-Task 1: Regression.

Systems will be ranked using the Root Mean Squared Error (RMSE) on the overall test set. The file uploaded for evaluation must be a zip file containing a csv file called "task-1-output.csv" having two columns in the following order:

id: the ID of the edited headline as provided in the dataset
pred: the estimated funniness for the headline, a real number in the 0-3 funniness interval.
Please include the column headers and name them exactly as above, and in the order mentioned. A sample output (for the baseline system) can be found here.

We will additionally report RMSE by taking the N% most funny headlines and N% least funny headlines in the test set, for N ∈ {10,20,30,40}. For example, N=30 implies sorting the test set from most funny to least funny and using the top 30% and the bottom 30% of this sorted data, for a total of 60% of the test set, to calculate the RMSE. These are meant to be additional evaluation metrics, and they will not be used to rank systems.

