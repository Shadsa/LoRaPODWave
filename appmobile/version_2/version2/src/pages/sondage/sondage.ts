import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { HttpClient } from '@angular/common/http';

export interface Config {
  url: string;
  textfile: string;
}

@Component({
  selector: 'page-sondage',
  templateUrl: 'sondage.html',
})

export class SondagePage {

  //Contains our informations
  compteurs: number[];
  //Used to show the percentages
  percentages: number[];
  //The options availables
  yesno: string[];
  //Might seen a rework. Data struct to send information
  options: Array<{title: string, value: number}>;

  //Config test for HTTP client


  constructor(public navCtrl: NavController, public navParams: NavParams,
  private httpC: HttpClient) {

    //Init the compteurs
    this.compteurs = [0,0,0];

    //Init the percentages
    this.percentages = [0,0,0];
  	//Add some basic options to our yesno
  	this.yesno = ["yes", "no"];

  	//Init options
  	this.options = [];
  	
  	//Fill the options
  	for (let i = 0; i < 2; i++) {
      this.options.push({
        title: this.yesno[i] ,
        value: i
      });
    }
  
  }

  itemTapped(event, option) {
    //DEBUG
    console.log(option.title);

    //Increase the right compteur, refresh the total counteré
    switch(option.title){
      case "yes" : this.compteurs[0]++;break;
      case "no" : this.compteurs[1]++;break;
      default:console.log('Erreur');
    }
    this.compteurs[2] = this.compteurs[0] + this.compteurs[1];
    this.percentages[0] = (this.compteurs[0] / this.compteurs[2]) * 100;
    this.percentages[1] = (this.compteurs[1] / this.compteurs[2]) * 100;
    this.percentages[2] = 100;
  }

  ionViewDidLoad() {
    console.log('BITE BITE BITE');
  }

  getCompteurYes(){
    return this.compteurs[0];
  }

  getCompteurNo(){
    return this.compteurs[1];
  }

  getCompteurTotal(){
    return this.compteurs[2];
  }

  getPercentageYes(){
    return this.percentages[0];
  }

  getPercentageNo(){
    return this.percentages[1];
  }

  getPercentageTotal(){
    return this.percentages[2];
  }
}
