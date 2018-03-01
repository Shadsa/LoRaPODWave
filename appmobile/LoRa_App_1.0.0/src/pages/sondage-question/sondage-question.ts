import { Component,Injectable } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs/Observable';
import 'rxjs/add/operator/map';

import {SondageAnswersPage} from '../sondage-answers/sondage-answers';

interface Post {
  userId: string;
  id: string;
  title: string;
  body: string;
}

@Component({
  selector: 'page-sondage-question',
  templateUrl: 'sondage-question.html',
})
export class SondageQuestionPage {

  listPosts :Observable<Post[]>;
  unestring :Observable<String>;

  constructor(public navCtrl: NavController, public navParams: NavParams,
  public httpC: HttpClient) {
      this.listPosts = this.httpC.get('https://jsonplaceholder.typicode.com/posts')
      .pluck('results');
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad SondageQuestionPage');
  }

  public getPost() : Observable<Post[]> {
    var ret: Observable<Post[]>;
    ret = this.httpC.get('https://jsonplaceholder.typicode.com/posts')
    .pluck('results');
    return ret;
  }
}
