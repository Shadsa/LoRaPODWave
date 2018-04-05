import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { HttpClient } from '@angular/common/http';
import { HttpParams } from '@angular/common/http';
import { Observable } from 'rxjs/Observable';
import { AlertController } from 'ionic-angular';
import { NUMBER_TYPE } from '@angular/compiler/src/output/output_ast';

//  id / value => an item of a json collection
//  num is the amount of time the item has been voted for
interface Answers_Collection {
  id : number;
  value : string;
  num : number;
}

//  the json object returned shall follow this interface :
//  a title and a collection of option on which vote 
//  & the total field, which is used to calculate the percentages
interface Answers_Result {
  title : string;
  collection : [Answers_Collection];
  total: number;
}

@Component({
  selector: 'page-sondage-answers',
  templateUrl: 'sondage-answers.html',
})

export class SondageAnswersPage {

  //  URL used to get the previous votes informations
  uneUrl : string = "http://192.168.4.1/GetPODResult";

  //  OBJECT used to store the informations the pod will send
  retResult : Answers_Result = null;

  constructor(public navCtrl: NavController, public navParams: NavParams,
    public httpC: HttpClient, public alertCtrl: AlertController) {
    this.setResult();
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad SondageAnswersPage');
  }

  //  get request to the get url ; return an observable following json syntax
  getResult() : Observable<Answers_Result>{
    return this.httpC.get<Answers_Result>(this.uneUrl);
  }

  //  launch a get request, and subscribe the observable to retResult
  setResult(){
    this.retResult = null;
    this.getResult().subscribe(res => this.retResult = res);
  }

  //  get the percentage associated with value
  convertPercentage(value, total) : string {
    var temp = (value/total) * 100;
    temp = Math.round(temp);
    return temp+"%";
  }

}
