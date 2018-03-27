LoRa PodWave Wifi-Server API Documentation :

Préambule et explication :


API Page-Serve

Note : le header doit être terminé par \n\n

API Routes : 

Récupération de donnée :

GetPODMeta() => Requête sur l’url 192.168.4.1/GetPODMeta renvoyant un JSON au format suivant :

GetPODData()=>Requête sur l’url 192.168.4.1/GetPODData renvoyant un JSON au format suivant :
{
Title : DataCollection
Collection : [{ id : index de la value coté serv  ,  value : string de la value},……]
}

GetPODResult()=>Requête sur l’url 192.168.4.1/GetPODResult renvoyant un JSON au format suivant :
{
Title : ResultCollection
Collection : [{ id : index de la value coté serv  ,  value : nombre devote pour la value d’index id},…..]
}





Mise à jour des données :

SendPODData(String VALUE) => Doit faire une requête GET contenant VALUE sur l’URL suivante : 192.168.4.1/UP(ou DOWN si on veux downvote)_VALUE.


Paramétrage du POD

UpdatePODParameter() => envois d’un requête get sur l’url 192.168.4.1 suivit de :
-	ADD_VALUE (string value)
-	REMOVE_VALUE (int index)
-	CLEAN_VALUE
-	RW_TRIGGER (String Trigger)
-	RW_CONDITION (String Condition)
-	CLEAN_ALL
Suivit, en concaténé sans espace ni signe, du paramètre adapté (entre paranthèse ci-dessus)
