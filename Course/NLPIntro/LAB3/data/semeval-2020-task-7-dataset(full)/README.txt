@Author: Nabil Hossain
 	 nhossain@cs.rochester.edu
Date: 05/21/2020

This is the task dataset for SemEval-2020 Task 7: Assessing Humor in Edited News Headlines.

Please cite the task paper when using this dataset:

Nabil Hossain, John Krumm, Michael Gamon and Henry Kautz. 2020. Semeval-2020 Task 7: Assessing Humor in Edited News Headlines. In Proceedings of International Workshop on Semantic Evaluation (SemEval-2020), Barcelona, Spain, September 2020.

BIBTEX: 
@InProceedings{SemEval2020Task7, author = {Hossain, Nabil and Krumm, John and Gamon, Michael and Kautz,Henry}, title = {SemEval-2020 {T}ask 7: {A}ssessing Humor in Edited News Headlines}, booktitle = {Proceedings of the 14th International Workshop on Semantic Evaluation ({S}em{E}val-2020)}, address = {Barcelona, Spain}, year = {2020}}

CodaLab page hosting the competition:
https://competitions.codalab.org/competitions/20970

Starter Github code (scripts for running baseline and evaluation):
https://github.com/n-hossain/semeval-2020-task-7-humicroedit

Task mailing list:
https://groups.google.com/forum/#!forum/semeval-2020-task-7-all
----------------------------------------------------------------------

ZIP contents:
-------------

Folders:
	- subtask-1: Dataset for the funniness regression subtask.
	- subtask-2: Dataset for the "Funnier of the Two" classification subtask.

Files:
	- {train, dev, test}.csv: the task's dataset including labels
	- train_funlines.csv: additional training data gathered from the FunLines competition (https://funlines.co)
	- baseline.zip: contains csv file which is the output of the BASELINE system. This is a template of the output format that can be submitted to CodaLab for scoring.
