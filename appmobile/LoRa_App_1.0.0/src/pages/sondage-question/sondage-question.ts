import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { HttpClient, HttpParams, HttpHeaders} from '@angular/common/http';
import { Observable } from 'rxjs/Observable';
import 'rxjs/add/operator/map';
import { AlertController } from 'ionic-angular';
import {SondageAnswersPage} from '../sondage-answers/sondage-answers';

//  id / value => an item of a json collection
interface Question_Collection {
  id : number;
  value : string;
}

//  the json object returned shall follow this interface :
//  a title and a collection of option on which vote 
interface Question_Result {
  title : string;
  collection : [Question_Collection];
}

//  to bypass the security ; allow several request
const httpOptions = {
  headers : new HttpHeaders({ 
    'Access-Control-Allow-Origin':'*'
  })
};

@Component({
  selector: 'page-sondage-question',
  templateUrl: 'sondage-question.html',
})

export class SondageQuestionPage {
  //uneUrl : string = "https://api.myjson.com/bins/q2gph";

  //  URL used to get informations from the pod
  urlGet : string = "http://192.168.4.1/GetPODData";

  //  URL used to push informations to the pod
  urlPush : string = "http://192.168.4.1/UP_";

  //  OBJECT used to store the informations from the pod
  retResult : Question_Result = null;

  //  OBJECT hack to force the execution of the push request
  tempResult : any = null;
  
  constructor(public navCtrl: NavController, public navParams: NavParams,
  public httpC: HttpClient, public alertCtrl: AlertController) {
    this.setResult(); //get the initial informations on loading of the page
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad SondageQuestionPage');
  }

  //  get request to the get url ; return an observable following json syntax
  getResult() : Observable<Question_Result>{
    return this.httpC.get<Question_Result>(this.urlGet);
  }

  //  launch a get request, and subscribe the observable to retResult
  setResult(){
    this.getResult().subscribe(res => this.retResult = res);
  }

  //  get (TODO) request to the push URL to send the vote
  voteFor(id) {
    console.log("voted for :");
    console.log(this.urlPush+id);
    return this.httpC.get(this.urlPush+id);
  }

  //  force the get request to happens ; the observable isn't used
  sendResult(id) {
    this.voteFor(id).subscribe(res => this.tempResult = res);
  }

  //  handle the click on a button
  buttonClicked(value, id){
    let alert = this.alertCtrl.create({
      title: 'Confirm vote',
      message: 'Do you want to vote for '+ value +'?',
      buttons: [
        {
          text: 'Cancel',
          role: 'cancel',
          handler: () => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Confirm',
          handler: () => {
            console.log('Confirm '+ id +' clicked');
            this.sendResult(value);
          }
        }
      ]
    });
    alert.present();
  }
}
