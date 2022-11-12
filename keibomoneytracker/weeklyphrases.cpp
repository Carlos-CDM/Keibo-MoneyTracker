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


std::string WeeklyPhrases::getQuoteOfTheWeek(const Language &iLanguage) //Call this function in void Gui_BuyData::updateUiToLanguage(const Language &iLanguage)
{
    time_t T = time(0);
    struct tm * currentTime = localtime(&T);
    unsigned int currentMonth = currentTime->tm_mon;
    unsigned int currentDayInMonth = currentTime->tm_mday;

        std::string currentPhrase;

        if (iLanguage == ENGLISH)
        {
            switch (currentMonth) {
            case 0:
            {
                if (currentDayInMonth < 14u)
                {
                   currentPhrase = "“If you cannot measure it, you cannot manage it.” \t(Peter Drucker)";
                }
                else
                {
                    currentPhrase = "“Pay attention to your mind. Make sure that fear is not what motivates your actions.”";
                }
                break;
            }
            case 1:
            {
                if (currentDayInMonth < 13u)
                {
                    currentPhrase = "“It's not that I'm so smart. It's that I stay with problems longer.” \t(Albert Einstein)";
                }
                else
                {
                    currentPhrase = "“Money carries our intention. If we use it with integrity, then it carries integrity forward.” \t(Lynne Twist)";
                }
                break;
            }
            case 2:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“When someone arouses your anger, know that it's really your own opinion fueling it.” \t(Epictetus)";
                }
                else
                {
                    currentPhrase = "“The more you share and the more generous you are with your time, talents and gifts, the more abundance will flow to you.” \t(Ken Honda)";
                }
                break;
            }
            case 3:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“The primary cause of unhappiness is never the situation itself but your thoughts about it.” \t(Eckhart Tolle)";
                }
                else
                {
                    currentPhrase = "“In the middle of difficulty lies opportunity.” \t(Albert Einstein)";
                }
                break;
            }
            case 4:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Never give up on a dream just because of the time it will take to accomplish it. The time will pass anyway.” \t(Earl Nightingale)";
                }
                else
                {
                    currentPhrase = "If you are getting too much ask yourself: Do I really need this? What could happen if I don't get it? Can I go on without it?";
                }
                break;
            }
            case 5:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Constantly feeling that you deserve more is a dangerous way to live.” \t(Ken Honda)";
                }
                else
                {
                    currentPhrase = "“The power of unfulfilled desires is the root of all of man’s slavery.” \t(Paramahansa Yogananda)";
                }
                break;
            }
            case 6:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Let all your efforts be directed to something, let it keep that end in view.” \t(Seneca)";
                }
                else
                {
                    currentPhrase = "“He who knows, tells it not; he who tells, knows it not.” \t(Lao-Tzu)";
                }
                break;
            }
            case 7:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Freedom isn't secured by filling up on your heart's desire but by removing your desire.” \t(Epictetus)";
                }
                else
                {
                    currentPhrase = "“Perfection is achieved, not when there is nothing more to add, but when there is nothing left to take away.” \t(Antoine de Saint-Exupery)";
                }
                break;
            }
            case 8:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“The more I let go, the freer I became.” \t(Michael A. Singer, The Surrender Experiment: My Journey into Life's Perfection)";
                }
                else
                {
                    currentPhrase = "“If you cannot control your emotions you cannot control your money.” \t(Warren Buffet)";
                }
                break;
            }
            case 9:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Flow is an optimal state in which you feel totally engaged in an activity, you're neither bored not anxious.” \t(Mihaly Csikszentmihalyi)";
                }
                else
                {
                    currentPhrase = "“Your income is determined by how many people you serve and how well you serve them.” \t(Bob Burg and John David Mann - The Go-Giver)";
                }
                break;
            }
            case 10:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Sometimes life or our job is difficult enough, let's not make it harder by getting emotional about insignificant matters.” \t(Ryan Holiday, The Daily Stoic)";
                }
                else
                {
                    currentPhrase = "“Only when the last tree has been cut down, the last fish been caught and the last stream poisoned, will we realize we cannot eat money.” \t(Native American Proverb)";
                }
                break;
            }
            case 11:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“We become what we think about.” \t(Earl Nightingale)";
                }
                else
                {
                    currentPhrase = "“Life is what happens to you while you are busy making other plans.” \t(John Lennon)";
                }
                break;
            }
            default:
                currentPhrase = "No phrase available.";
                break;
            }
        }
        else if (iLanguage == GERMAN)
        {
            switch (currentMonth) {
            case 0:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "„Wenn Sie es nicht messen können, können Sie es nicht verwalten.“ \t(Peter Drucker)";
                }
                else
                {
                    currentPhrase = "“Achte auf deinen Verstand. Stell dich sicher, dass es nicht Angst ist, die dein Handeln motiviert.”";
                }
                break;
            }
            case 1:
            {
                if (currentDayInMonth < 13u)
                {
                    currentPhrase = "„Ich habe keine besondere Begabung, sondern bin nur leidenschaftlich neugierig.“ \t(Albert Einstein)";
                }
                else
                {
                    currentPhrase = "“Geld trägt unsere Absichten. Wenn wir es mit Aufrichtigkeit nutzen, trägt es diese weiter.” \t(Lynne Twist)";
                }
                break;
            }
            case 2:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "„Wenn jemand Ihren Ärger erregt, beachten Sie, dass es nur Ihre eigene Meinung ist, die diesen anfeuert.“ \t(Epictetus)";
                }
                else
                {
                    currentPhrase = "“Je mehr du von dir selbst teilst und je großzügiger du mit deiner Zeit, Talenten und Fähigkeiten bist, desto mehr Fülle wird zu dir kommen.” \t(Ken Honda)";
                }
                break;
            }
            case 3:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "„Der Hauptgrund für Unglück ist niemals die Situation selbst, sondern deine Wahrnehmung dieser Situation.“ \t(Eckhart Tolle)";
                }
                else
                {
                    currentPhrase = "“Inmitten von Schwierigkeiten liegen Möglichkeiten.” \t(Albert Einstein)";
                }
                break;
            }
            case 4:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "„Gib niemals einen Traum auf, nur wegen der Zeit, die es braucht, um ihn zu verwirklichen. Die Zeit vergeht sowieso.“ \t(Earl Nightingale)" ;
                }
                else
                {
                    currentPhrase = "Wenn du zu viel bekommst, frag dich zuerst: Brauche ich das wirklich? Was könnte passieren, wenn ich es nicht bekomme? Kann ich auch ohne weitermachen?";
                }
                break;
            }
            case 5:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Ständig das Gefühl zu fühlen mehr verdient zu haben, ist ein gefährlicher Art zu leben.” \t(Ken Honda)";
                }
                else
                {
                    currentPhrase = "“In der Kraft von unerfüllten Wünschen liegt die Wurzel der Sklaverei.” \t(Paramahansa Yogananda)";
                }
                break;
            }
            case 6:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "„Lassen Sie alle Ihre Bemühungen auf etwas gerichtet und behalten das Ende dabei im Blick.“ \t(Seneca)";
                }
                else
                {
                    currentPhrase = "“Der der es weiß, sagt es nicht. Der der es sagt, weiß es nicht.” \t(Lao-Tzu)";
                }
                break;
            }
            case 7:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "„Freiheit wird nicht dadurch gesichert, dass du den Wunsch deines Herzens erfüllst, sondern indem du diesen Wunsch beseitigst.“ \t(Epictetus)";
                }
                else
                {
                    currentPhrase = "“Man erreicht nicht Perfektion, wenn es nichts mehr hinzuzufügen gibt, sondern, wenn man nichts mehr wegnehmen kann.” \t(Antoine de Saint-Exupery)";
                }
                break;
            }
            case 8:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "„Je mehr ich loslasse, desto freier werde ich.“ \t(Michael A. Singer, Das Experiment Hingabe: Mein Weg in die Vollkommenheit)";
                }
                else
                {
                    currentPhrase = "“Wenn du deine Emotionen nicht kontrollieren kannst, kannst du dein Geld nicht kontrollieren.” \t(Warren Buffet)";
                }
                break;
            }
            case 9:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "„Flow ist ein optimaler Zustand, in dem Sie sich total in eine Aktivität verwickelt fühlen, Sie sind weder gelangweilt noch ängstlich.“ \t(Mihaly Csikszentmihalyi)";
                }
                else
                {
                    currentPhrase = "“Dein Einkommen wird dadurch festgelegt wie vielen Menschen du dienst und wie gut du ihnen dienst.” \t(Bob Burg und John David Mann - The Go-Giver)";
                }
                break;
            }
            case 10:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "„Manchmal ist das Leben oder unser Job schwierig genug. Machen wir es uns nicht noch schwerer, indem wir uns über unbedeutende Dinge aufregen.“ \t(Ryan Holiday, Der tägliche Stoiker)";
                }
                else
                {
                    currentPhrase = "“Nur wenn der letzte Baum gefällt, der letzte Fisch gefangen und der letzte Bach vergiftet ist, werden wir erkennen, dass wir Geld nicht essen können.” \t(Sprichwort der amerikanischen Ureinwohner)";
                }
                break;
            }
            case 11:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "„Wir werden das, was wir denken.“ \t(Earl Nightingale)";
                }
                else
                {
                    currentPhrase = "“Das Leben ist das, was passiert, während du andere Pläne schmiedest.” \t(John Lennon)";
                }
                break;
            }
            default:
                currentPhrase = "Kein Zitat verfügbar.";
                break;
            }
        }
        else if (iLanguage == SPANISH)
        {
            switch (currentMonth) {
            case 0:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Si no se puede medir, no se puede gestionar.” \t(Peter Drucker)";
                }
                else
                {
                    currentPhrase = "“Pon atención a lo que piensas. Asegurate de que no es miedo lo que motiva tus acciones.”";
                }
                break;
            }
            case 1:
            {
                if (currentDayInMonth < 13u)
                {
                    currentPhrase = "“No es que yo sea muy listo. Es que me quedo con los problemas por mas tiempo.” \t(Albert Einstein)";
                }
                else
                {
                    currentPhrase = "“El dinero lleva consigo nuestra intención. Si lo usamos con integridad, lleva y promueve integridad.” \t(Lynne Twist)";
                }
                break;
            }
            case 2:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Cuando alguien te haga enojar, está consciente de que es tu propia opinión alimentando el sentimiento.” \t(Epicteto)";
                }
                else
                {
                    currentPhrase = "“Entre mas compartes y mas generoso eres con tu tiempo, talentos y habilidades, mas abundancia fluirá hacia tí.” \t(Ken Honda)";
                }
                break;
            }
            case 3:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“La causa principal de infelicidad nunca es la situación misma, sino tus pensamientos sobre ella.” \t(Eckhart Tolle)";
                }
                else
                {
                    currentPhrase = "“Entre las dificultades se esconde la oportunidad.” \t(Albert Einstein)";
                }
                break;
            }
            case 4:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Nunca te des por vencido debido al tiempo que tus proyectos necesitarán, el tiempo pasará de todas maneras.” \t(Earl Nightingale)";
                }
                else
                {
                    currentPhrase = "Si estás acumulando demasiado preguntate: Realmente necesito esto? Que pasaría si no lo obtengo? Puedo continuar sin poseerlo?";
                }
                break;
            }
            case 5:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Constantemente creyendo que mereces más es una manera peligrosa de vivir.” \t(Ken Honda)";
                }
                else
                {
                    currentPhrase = "“En el poder de los deseos sin cumplir está la raíz de la exclavitud del hombre.” \t(Paramahansa Yogananda)";
                }
                break;
            }
            case 6:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Dirige todos tus esfuerzos hacia algo y mantén esa meta en vista.” \t(Seneca)";
                }
                else
                {
                    currentPhrase = "“Aquel que sabe, no lo dice; aquel que dice, no lo sabe.” \t(Lao-Tzu)";
                }
                break;
            }
            case 7:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“La libertad no está asegurada al cumplir los deseos de tu corazón, sino al removerlos de él.” \t(Epicteto)";
                }
                else
                {
                    currentPhrase = "“La perfección no se logra cuando no hay nada mas que añadir, sino nadamas que quitar.” \t(Antoine de Saint-Exupery)";
                }
                break;
            }
            case 8:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Entré mas dejé ir, más libre fuí.” \t(Michael A. Singer, El experimento rendición : el encuentro con la perfección de la vida)";
                }
                else
                {
                    currentPhrase = "“Si no puedes controlar tus emociones, no puedes controlar tu dinero.” \t(Warren Buffet)";
                }
                break;
            }
            case 9:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Flujo es un estado óptimo en el cual te sientes totalmente inmerso en una actividad, no estás ni aburrido ni ansioso.” \t(Mihaly Csikszentmihalyi)";
                }
                else
                {
                    currentPhrase = "“Tus ingresos están determinados por dos cosas; el número de personas a las que sirves y que tan bien les sirves.” \t(Bob Burg y John David Mann - The Go-Giver)";
                }
                break;
            }
            case 10:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“A veces la vida o el trabajo son difíciles po sí solos, no los hagámos mas difícil poniéndonos emocionales por problemas insignificantes.” \t(Ryan Holiday, Estoicismo cotidiano)";
                }
                else
                {
                    currentPhrase = "“Solo cuando el último árbol sea cortado, el último pez atrapado y el ultimo arroyo envenenado, nos daremos cuenta que no podemos comer dinero.” \t(Proverbio Nativo Americano)";
                }
                break;
            }
            case 11:
            {
                if (currentDayInMonth < 14u)
                {
                    currentPhrase = "“Nos convertimos en lo que pensamos.” \t(Earl Nightingale) ";
                }
                else
                {
                    currentPhrase = "“La vida es aquello que te va sucediendo mientras te empeñas en hacer otros planes.” \t(John Lennon)";
                }
                break;
            }
            default:
                currentPhrase = "Frase no disponible.";
                break;
            }
        }


    return currentPhrase;
}
