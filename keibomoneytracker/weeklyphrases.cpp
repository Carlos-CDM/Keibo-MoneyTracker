/*
* Copyright © 2020 Carlos Constancio Dominguez Martinez
*
* This file is part of Keibo-MoneyTracker
*
* Keibo-MoneyTracker is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Keibo-MoneyTracker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
* Authored by: Carlos Constancio Dominguez Martinez <dmartinez.carlos@gmail.com>
*/

#include "weeklyphrases.h"
#include <ctime>
#include <iostream>

WeeklyPhrases::WeeklyPhrases()
{

}

std::string WeeklyPhrases::getPhraseOfTheWeek(const Language &iLanguage) //Call this function in void Gui_BuyData::updateUiToLanguage(const Language &iLanguage)
{
    time_t T = time(0);
    struct tm * currentTime = localtime(&T);
    int currentMonth = currentTime->tm_mon;

        std::string currentPhrase;

        if (iLanguage == ENGLISH)
        {
            switch (currentMonth) {
            case 0:
            {
                currentPhrase = "“If you cannot measure it, you cannot manage it.” \t(Peter Drucker)";
                break;
            }
            case 1:
            {
                currentPhrase = "“It's not that I'm so smart. It's that I stay with problems longer.” \t(Albert Einstein)";
                break;
            }
            case 2:
            {
                currentPhrase = "“When someone arouses your anger, know that it's really your own opinion fueling it.” \t(Epictetus)";
                break;
            }
            case 3:
            {
                currentPhrase = "“The primary cause of unhappiness is never the situation itself but your thoughts about it.” \t(Eckhart Tolle)";
                break;
            }
            case 4:
            {
                currentPhrase = "“Never give up on a dream just because of the time it will take to accomplish it. The time will pass anyway.” \t(Earl Nightingale)";
                break;
            }
            case 5:
            {
                currentPhrase = "If you are getting too much ask yourself: Do I really need this? What could happen if I don't get it? Can I go on without it?";
                break;
            }
            case 6:
            {
                currentPhrase = "“Let all your efforts be directed to something, let it keep that end in view.” \t(Seneca)";
                break;
            }
            case 7:
            {
                currentPhrase = "“Freedom isn't secured by filling up on your heart's desire but by removing your desire.” \t(Epictetus)";
                break;
            }
            case 8:
            {
                currentPhrase = "“The more I let go, the freer I became.” \t(Michael A. Singer, The Surrender Experiment: My Journey into Life's Perfection)";
                break;
            }
            case 9:
            {
                currentPhrase = "“Flow is an optimal state in which you feel totally engaged in an activity, you're neither bored not anxious.” \t(Mihaly Csikszentmihalyi)";
                break;
            }
            case 10:
            {
                currentPhrase = "“Sometimes life or our job is difficult enough, let's not make it harder by getting emotional about insignificant matters.” \t(Ryan Holiday, The Daily Stoic)";
                break;
            }
            case 11:
            {
                currentPhrase = "“We become what we think about.” \t(Earl Nightingale)";
                break;
            }
            default:
                currentPhrase = "No phrase available";
                break;
            }
        }
        else if (iLanguage == GERMAN)
        {
            switch (currentMonth) {
            case 0:
            {
                currentPhrase = "„Wenn Sie es nicht messen können, können Sie es nicht verwalten.“ \t(Peter Drucker)";
                break;
            }
            case 1:
            {
                currentPhrase = "„Ich habe keine besondere Begabung, sondern bin nur leidenschaftlich neugierig.“ \t(Albert Einstein)";
                break;
            }
            case 2:
            {
                currentPhrase = "„Wenn jemand Ihren Ärger erregt, beachten Sie, dass es nur Ihre eigene Meinung ist, die diesen anfeuert.“ \t(Epictetus)";
                break;
            }
            case 3:
            {
                currentPhrase = "„Der Hauptgrund für Unglück ist niemals die Situation selbst, sondern deine Wahrnehmung dieser Situation.“ \t(Eckhart Tolle)";
                break;
            }
            case 4:
            {
                currentPhrase = "„Gib niemals einen Traum auf, nur wegen der Zeit, die es braucht, um ihn zu verwirklichen. Die Zeit vergeht sowieso.“ \t(Earl Nightingale)" ;
                break;
            }
            case 5:
            {
                currentPhrase = "Wenn Sie zu viel bekommen, fragen Sie sich zuerst: Brauche ich das wirklich? Was könnte passieren, wenn ich es nicht bekomme? Kann ich auch ohne weitermachen?";
                break;
            }
            case 6:
            {
                currentPhrase = "„Lassen Sie alle Ihre Bemühungen auf etwas gerichtet und behalten das Ende dabei im Blick.“ \t(Seneca)";
                break;
            }
            case 7:
            {
                currentPhrase = "„Freiheit wird nicht dadurch gesichert, dass Sie den Wunsch Ihres Herzens erfüllen, sondern indem Sie diesen Wunsch beseitigen.“ \t(Epictetus)";
                break;
            }
            case 8:
            {
                currentPhrase = "„Je mehr ich loslasse, desto freier werde ich.“ \t(Michael A. Singer, Das Experiment Hingabe: Mein Weg in die Vollkommenheit)";
                break;
            }
            case 9:
            {
                currentPhrase = "„Flow ist ein optimaler Zustand, in dem Sie sich total in eine Aktivität verwickelt fühlen, Sie sind weder gelangweilt noch ängstlich.“ \t(Mihaly Csikszentmihalyi)";
                break;
            }
            case 10:
            {
                currentPhrase = "„Manchmal ist das Leben oder unser Job schwierig genug. Machen wir es uns nicht noch schwerer, indem wir uns über unbedeutende Dinge aufregen.“ \t(Ryan Holiday, Der tägliche Stoiker)";
                break;
            }
            case 11:
            {
                currentPhrase = "„Wir werden das, was wir denken.“ \t(Earl Nightingale)";
                break;
            }
            default:
                currentPhrase = "No phrase available";
                break;
            }
        }
        else if (iLanguage == SPANISH)
        {
            switch (currentMonth) {
            case 0:
            {
                currentPhrase = "“Si no se puede medir, no se puede gestionar.” \t(Peter Drucker)";
                break;
            }
            case 1:
            {
                currentPhrase = "“No es que yo sea muy listo. Es que me quedo con los problemas por mas tiempo.” \t(Albert Einstein)";
                break;
            }
            case 2:
            {
                currentPhrase = "“Cuando alguien te haga enojar, está consciente de que es tu propia opinión alimentando el sentimiento.” \t(Epicteto)";
                break;
            }
            case 3:
            {
                currentPhrase = "“La causa principal de infelicidad nunca es la situación misma, sino tus pensamientos sobre ella.” \t(Eckhart Tolle)";
                break;
            }
            case 4:
            {
                currentPhrase = "“Nunca te des por vencido debido al tiempo que tus proyectos necesitarán, el tiempo pasará de todas maneras.” \t(Earl Nightingale)";
                break;
            }
            case 5:
            {
                currentPhrase = "Si estás acumulando demasiado preguntate: Realmente necesito esto? Que pasaría si no lo obtengo? Puedo continuar sin poseerlo?";
                break;
            }
            case 6:
            {
                currentPhrase = "“Dirige todos tus esfuerzos hacia algo y mantén esa meta en vista.” \t(Seneca)";
                break;
            }
            case 7:
            {
                currentPhrase = "“La libertad no está asegurada al cumplir los deseos de tu corazón, sino al removerlos de él.” \t(Epicteto)";
                break;
            }
            case 8:
            {
                currentPhrase = "“Entré mas dejé ir, más libre fuí.” \t(Michael A. Singer, El experimento rendición : el encuentro con la perfección de la vida)";
                break;
            }
            case 9:
            {
                currentPhrase = "“Flujo es un estado óptimo en el cual te sientes totalmente inmerso en una actividad, no estás ni aburrido ni ansioso.” \t(Mihaly Csikszentmihalyi)";
                break;
            }
            case 10:
            {
                currentPhrase = "“A veces la vida o el trabajo son difíciles po sí solos, no los hagámos mas difícil poniéndonos emocionales por problemas insignificantes.” \t(Ryan Holiday, Estoicismo cotidiano)";
                break;
            }
            case 11:
            {
                currentPhrase = "“Nos convertimos en lo que pensamos.” \t(Earl Nightingale) ";
                break;
            }
            default:
                currentPhrase = "No phrase available";
                break;
            }
        }


    return currentPhrase;
}
