import { BrowserModule } from '@angular/platform-browser';
import { ErrorHandler, NgModule } from '@angular/core';
import { IonicApp, IonicErrorHandler, IonicModule } from 'ionic-angular';
import { SplashScreen } from '@ionic-native/splash-screen';
import { StatusBar } from '@ionic-native/status-bar';
import {HttpClientModule} from '@angular/common/http';

import { MyApp } from './app.component';
import { HomePage } from '../pages/home/home';
import { SondagePage } from '../pages/sondage/sondage';
import {SondageAnswersPage} from '../pages/sondage-answers/sondage-answers';
import {SondageQuestionPage} from '../pages/sondage-question/sondage-question';

@NgModule({
  declarations: [ 
    MyApp,
    HomePage,
    SondagePage,
    SondageAnswersPage,
    SondageQuestionPage
  ],
  imports: [
    BrowserModule,
    IonicModule.forRoot(MyApp),
    HttpClientModule,
  ],
  bootstrap: [IonicApp],
  entryComponents: [
    MyApp,
    HomePage,
    SondagePage,
    SondageAnswersPage,
    SondageQuestionPage
  ],
  providers: [
    StatusBar,
    SplashScreen,
    {provide: ErrorHandler, useClass: IonicErrorHandler}
  ]
})
export class AppModule {}
