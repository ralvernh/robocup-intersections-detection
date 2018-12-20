# robocup-intersections-detection

	-> codes c++ et makefile (Dossier "CODES") 
	
	-> codes python (Dossier "")
	
	-> nécessité d'un dossier "data_2" : y intégrer les images à visualiser (téléchargées des archives du projet) 

	-> nécessité d'un dossier "super_templates"; contenant les templates à reconnaitre (uniquement pour les différentes versions de "matchingTemplate")

--------------------------------------------------------------------------------------------------------------------------------
Pour le makefile;
____________________

	1) sélectionner le dossier contenant les images à exécuter dans le programme "data", "data_2" ou autre ...
	
	2) sélectionner l'image au format png à exécuter (dans le dossier choisi précédamment)
	
	3) sélectionner les codes à exécuter ou non
	
codes c++:
____________
	
Dans un terminal, se placer dans le dossier CODES.

make : lance la compilation des codes sélectionnés

make test : lance leurs exécutions

---------------------------------------------------------------------------------------------------------------------------------

codes python:
______________

utiliser le jupyter notbook (ou autre...)
------------------------------------------------------------------------------------








-> essayer d'implémenter un cnn + tracking: sources utiles: 
https://medium.com/nybles/create-your-first-image-recognition-classifier-using-cnn-keras-and-tensorflow-backend-6eaab98d14dd
(source de 'cnn.py')
https://medium.com/@kylepob61392/airplane-image-classification-using-a-keras-cnn-22be506fdb53   (très utile)
https://towardsdatascience.com/basics-of-image-classification-with-keras-43779a299c8b   (très utile)

Utilisation d'un algo "YOLO":
https://towardsdatascience.com/object-detection-using-google-ai-open-images-4c908cad4a54
https://github.com/bandiatindra/Object-Detection-Project/blob/master/Object%20Detection%20on%20Google%20Open%20AI%20Images.ipynb

principe "YOLO":

https://towardsdatascience.com/evolution-of-object-detection-and-localization-algorithms-e241021d8bad
