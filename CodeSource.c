// on declare les bibiliotheques necessaire
#include <raylib.h>

// ici on definie un type qu'on appelle EcranDeJeu
typedef enum EcranDeJeu
{
  Accueil,
  MenuCouleur,
  EasterEgg,
  Niveau,
  Gameplay,
  Pause,
  fin
} EcranDeJeu;

// on declare des variables globales
Rectangle RaquetteG, RaquetteD, Balle, ecran;
// pour la vitesse de la balle
int Vx = 350, Vy = 350;
// pour la vitesse de la raquette
int VitesseRaquetteG = 350, VitesseRaquetteD = 350;
// pour le score au debut
int ScoreJoueur = 0, ScoreOrdi = 0, gagnant = 0;
// valeur de la fenetre
int LargeurEcran = 1200, HauteurEcran = 700, Couleur;

int difficulte, Couleur;

// un booleen pour verifier l'etat de la musique
bool mute = true;

// la fonction pour initialiser le jeu
void InitialiserPong(void)
{

  InitWindow(LargeurEcran, HauteurEcran, "JeuPong Original");
  RaquetteG = (Rectangle){10, GetScreenHeight() / 2 - 150 / 2, 20, 150};
  RaquetteD = (Rectangle){GetScreenWidth() - 30, GetScreenHeight() / 2 - 150 / 2, 20, 150};
  Balle = (Rectangle){GetScreenWidth() / 2.0f - 8, GetScreenHeight() / 2.0f, 15, 15};
  ecran = (Rectangle){0, 0, LargeurEcran, HauteurEcran};
}
// la fontion pour l'affichage
void AfficherPong(int Couleur)
{
  if (Couleur == 0)
  {
    ClearBackground(BLACK);
    DrawRectangle(RaquetteG.x, RaquetteG.y, RaquetteG.width, RaquetteG.height, WHITE);
    DrawRectangle(RaquetteD.x, RaquetteD.y, RaquetteD.width, RaquetteD.height, WHITE);
    DrawRectangle(Balle.x, Balle.y, Balle.width, Balle.height, WHITE);
    DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);
    DrawRectangle(ecran.width / 2, 0, 7, ecran.height, WHITE);
    DrawText(TextFormat("%d", ScoreJoueur), GetScreenWidth() / 2 + 65, 20, 40, WHITE);
    DrawText(TextFormat("%d", ScoreOrdi), GetScreenWidth() / 2 - 80, 20, 40, WHITE);
  }

  if (Couleur == 1)
  {
    ClearBackground(BLUE);
    DrawRectangle(RaquetteG.x, RaquetteG.y, RaquetteG.width, RaquetteG.height, BLACK);
    DrawRectangle(RaquetteD.x, RaquetteD.y, RaquetteD.width, RaquetteD.height, RED);
    DrawRectangle(Balle.x, Balle.y, Balle.width, Balle.height, BLACK);
    DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), BLACK);
    DrawRectangle(ecran.width / 2, 0, 7, ecran.height, BLACK);
    DrawText(TextFormat("%d", ScoreJoueur), GetScreenWidth() / 2 + 65, 20, 40, BLACK);
    DrawText(TextFormat("%d", ScoreOrdi), GetScreenWidth() / 2 - 80, 20, 40, BLACK);
  }

  if (Couleur == 2)
  {
    ClearBackground(BLACK);
    DrawRectangle(RaquetteG.x, RaquetteG.y, RaquetteG.width, RaquetteG.height, RED);
    DrawRectangle(RaquetteD.x, RaquetteD.y, RaquetteD.width, RaquetteD.height, RED);
    DrawRectangle(Balle.x, Balle.y, Balle.width, Balle.height, RED);
    DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), RED);
    DrawRectangle(ecran.width / 2, 0, 7, ecran.height, RED);
    DrawText(TextFormat("%d", ScoreJoueur), GetScreenWidth() / 2 + 65, 20, 40, RED);
    DrawText(TextFormat("%d", ScoreOrdi), GetScreenWidth() / 2 - 80, 20, 40, RED);
  }
}
// la fonction pour le deplacement de la balle
void DeplacerBalle(void)
{
  Balle.x += Vx * GetFrameTime();
  Balle.y += Vy * GetFrameTime();
}
// fonction pour que la balle rebonde a chaque fois qu'elle touche le bord superieur ou inferieur
void RebondirBalleBord(void)
{
  if (Balle.y > GetScreenHeight() || Balle.y < 0)
  {
    Vy *= -1;
  }
}
// fonction pour faire rebondir la balle a chaque fois qu'elle sera touche par l'une des deux raquettes
void RebondirBalleRaquette(void)
{
  if (CheckCollisionRecs(Balle, RaquetteD)) // pour la requette droite
  {
    if (Vx > 0)
    {
      Vx *= -1.1f;
      Vy = (Balle.y - RaquetteD.y) / (RaquetteD.height / 2) * Vx;
    }
  }
  if (CheckCollisionRecs(Balle, RaquetteG)) // pour la raquette gauche
  {
    if (Vx < 0)
    {
      Vx *= -1.1f;
      Vy = (Balle.y - RaquetteG.y) / (RaquetteG.height / 2) * -Vx;
    }
  }
}
// fonction pour bouger la raquette du joueur avec les les touches Z et S
void BougerRaquette(void)
{
  if (IsKeyDown(KEY_W)) // la raquette remonte quand on appuie sur Z (W en QWERTY)
  {
    if (RaquetteG.y > 0)
    {
      RaquetteG.y -= VitesseRaquetteG * GetFrameTime() + 0.1;
    }
  }
  if (IsKeyDown(KEY_S)) // la raquette descent quand on appuie sur S
  {
    if (RaquetteG.y < HauteurEcran / 1.23)
    {
      RaquetteG.y += VitesseRaquetteG * GetFrameTime() + 0.1;
    }
  }
  // Ceci est une petite triche qui nous permet d'accelerer la raquette du joueur en appuiytant sur SHIFT ;)
  if (IsKeyDown(KEY_LEFT_SHIFT))
  {
    VitesseRaquetteG = 650;
  }
  // si vous voulez annuler la triche appuyez sur control gauche
  if (IsKeyDown(KEY_LEFT_CONTROL))
  {
    VitesseRaquetteG = 350;
  }
}
// fonction pour le bot
void BotRaquette(void)
{
  if (Balle.x > GetScreenHeight() / 2 && Balle.x <= GetScreenWidth())
  {
    if (RaquetteD.y + RaquetteD.height / 2 < Balle.y)
    {
      RaquetteD.y += VitesseRaquetteD * GetFrameTime() + 0.1;
    }
    if (RaquetteD.y + RaquetteD.height / 2 > Balle.y)
    {
      RaquetteD.y -= VitesseRaquetteD * GetFrameTime() + 0.1;
    }
  }
}
// la fonction pour servir la balle apres un but marquer
void ServirBalle(int difficulte)
{
  Balle.x = GetScreenWidth() / 2;
  Balle.y = GetScreenHeight() / 2;
  switch (difficulte)
  {
  case 1:
  {
    Vx = 350;
    Vy = 350;
    break;
  }
  case 2:
  {
    Vx = 500;
    Vy = 500;
    break;
  }
  case 3:
  {
    Vx = 700;
    Vy = 700;
    break;
  }
  default:
    break;
  }
}
// la fontion pour incrementer le compteur a chaque but marquer
void IncrementerCompteur(void)
{
  if (Balle.x < 0)
  {
    ScoreJoueur++;
    ServirBalle(difficulte);
  }
  else
  {
    if (Balle.x > GetScreenWidth())
    {
      ScoreOrdi++;
      ServirBalle(difficulte);
    }
  }
}
// ecran winner pour afficher different ecran pour chaque terrain de jeu
void EcranGagnant(int Couleur)
{
  if (Couleur == 0)
  {
    ClearBackground(BLUE);
    DrawText("  YOU WIN !", 225, 200, 120, BLACK);
    DrawText("appuyer sur ESPACE pour rejoue", 50, 525, 20, BLACK);
    DrawText("appuyer sur TAB pour revenir a l'accueil", 50, 555, 20, BLACK);
    DrawText("appuyer sur ECHAP pour quitter", 50, 585, 20, BLACK);
  }

  if (Couleur == 1)
  {
    ClearBackground(BLACK);
    DrawText("  YOU WIN !", 225, 200, 120, BLUE);
    DrawText("appuyer sur ESPACE pour rejoue", 50, 525, 20, BLUE);
    DrawText("appuyer sur TAB pour revenir a l'accueil", 50, 555, 20, BLUE);
    DrawText("appuyer sur ECHAP pour quitter", 50, 585, 20, BLUE);
  }

  if (Couleur == 2)
  {
    ClearBackground(BLUE);
    DrawText("  YOU WIN !", 225, 200, 120, BLACK);
    DrawText("appuyer sur ESPACE pour rejoue", 50, 525, 20, BLACK);
    DrawText("appuyer sur TAB pour revenir a l'accueil", 50, 555, 20, BLACK);
    DrawText("appuyer sur ECHAP pour quitter", 50, 585, 20, BLACK);
  }
}
//  ecran loser pour afficher different ecran pour chaque terrain de jeu
void EcranLose(int Couleur)
{
  if (Couleur == 0)
  {
    ClearBackground(RED);
    DrawText("GAME OVER", 225, 200, 120, BLACK);
    DrawText("appuyer sur ESPACE pour rejoue", 50, 525, 20, BLACK);
    DrawText("appuyer sur TAB pour revenir a l'accueil", 50, 555, 20, BLACK);
    DrawText("appuyer sur ECHAP pour quitter", 50, 585, 20, BLACK);
  }

  if (Couleur == 1)
  {
    ClearBackground(BLACK);
    DrawText("GAME OVER", 225, 200, 120, RED);
    DrawText("appuyer sur ESPACE pour rejoue", 50, 525, 20, RED);
    DrawText("appuyer sur TAB pour revenir a l'accueil", 50, 555, 20, RED);
    DrawText("appuyer sur ECHAP pour quitter", 50, 585, 20, RED);
  }

  if (Couleur == 2)
  {
    ClearBackground(RED);
    DrawText("GAME OVER", 225, 200, 120, BLACK);
    DrawText("appuyer sur ESPACE pour rejoue", 50, 525, 20, BLACK);
    DrawText("appuyer sur TAB pour revenir a l'accueil", 50, 555, 20, BLACK);
    DrawText("appuyer sur ECHAP pour quitter", 50, 585, 20, BLACK);
  }
}
// cree une fonction pour pouvoir afficher le jeu en plein ecran
void ToggleFullScreenWindow(int LargeurEcran, int HauteurEcran)
{
  // Verifier Si nous ne somme pas en plein ecran et recuperer quelle est es connecté actuelement
  if (!IsWindowFullscreen())
  {
    int EcranPC = GetCurrentMonitor();
    // Obtenir la largeur et la hauteur de notre moniteur
    ToggleFullscreen();
    SetWindowSize(GetMonitorWidth(EcranPC), GetMonitorHeight(EcranPC));
    // Basculer en plein ecran
  }
  // Si nous somme en plein ecran cela nous remettera en taille definie
  else
  {
    ToggleFullscreen();
    SetWindowSize(LargeurEcran, HauteurEcran);
  }
}

// ceci est une fonction pour crediter les devlopeur
void afficherEgg(void)
{
  ClearBackground(BLACK);
  DrawText("Ce code est réalisé :", 300, 100, 40, WHITE);
  DrawText("Guidjou Danil", 400, 150, 35, RED);
  DrawText("Choulak ahmed", 400, 185, 35, RED);
  DrawText("MEILLEUR PROJET", 145, 350, 100, WHITE);
  DrawText("MERCI DE JOUER A NOTRE JEU", 350, 600, 25, RED);
}

// la programme principale
int main()
{

  EcranDeJeu EcranActuelle = Accueil;

  InitialiserPong();

  InitAudioDevice(); // pour initialiser la musique
  Music music = LoadMusicStream("soundTrack.mp3");
  PlayMusicStream(music);
  // Ceci est la boucle qui permet de ne pas femer la Fenetre et verifiant la la touche espace ou l'icon pour fermer a ete pressée
  while (!WindowShouldClose())
  {
    UpdateMusicStream(music);
    // pour switch d'affichage
    switch (EcranActuelle)
    {

    // ici c'st pour acceder a l'ecran de jeu faut appuier sur entrer
    case Accueil:
    {
      // activer l'easter egg
      if (IsKeyPressed(KEY_F6))
      { // si l'utilisateur appuie sur F6 il vera les credis
        EcranActuelle = EasterEgg;
      }

      // continuer
      if (IsKeyPressed(KEY_ENTER))
      { // faudra appuier sur entrer pour continuer
        EcranActuelle = MenuCouleur;
      }

      // pour enlever la musique dans le menu accueil
      if (IsKeyPressed(KEY_F4))
        mute = !mute;
      if (mute)
      {
        SetMusicVolume(music, 1.0f);
      }
      else
      {
        SetMusicVolume(music, 0.0f);
      }
    }
    break;

    // pour quitter l'eater egg
    case EasterEgg:
    {
      afficherEgg();

      if (IsKeyPressed(KEY_F6))
      { // appuiyer sur F6
        EcranActuelle = Accueil;
      }
    }
    break;

      // ici le joueur devra choisir la couleur du terrain
    case MenuCouleur:
    {
      if (IsKeyPressed(KEY_B))
      { // B poue noir
        Couleur = 0;
        EcranActuelle = Niveau;
      }

      if (IsKeyPressed(KEY_T))
      { // T pour blue
        Couleur = 1;
        EcranActuelle = Niveau;
      }

      if (IsKeyPressed(KEY_R))
      { // R pour rouge
        Couleur = 2;
        EcranActuelle = Niveau;
      }
    }
    break;

    // ici le joueur devra choisir le mode de jeu
    case Niveau:
    {
      if (IsKeyPressed(KEY_D))
      { // D pour facile
        difficulte = 1;
        EcranActuelle = Gameplay;
      }

      if (IsKeyPressed(KEY_I))
      { // I pour moyen
        difficulte = 2;
        VitesseRaquetteD = 400;
        EcranActuelle = Gameplay;
      }

      if (IsKeyPressed(KEY_E))
      { // E pour difficile
        difficulte = 3;
        VitesseRaquetteD = 475;
        EcranActuelle = Gameplay;
      }
    }
    break;

    // la partie de jeu tout les appelle pour les fonctions
    case Gameplay:
    {
      DeplacerBalle();
      RebondirBalleBord();
      RebondirBalleRaquette();
      BougerRaquette();
      BotRaquette();
      IncrementerCompteur();
      // pour verifier le score et terminer la partie
      if (ScoreJoueur == 10)
      {
        gagnant = 1;
        EcranActuelle = fin;
        ScoreJoueur = ScoreOrdi = 0;
      }
      else
      {
        if (ScoreOrdi == 10)
        {
          gagnant = 2;
          EcranActuelle = fin;
          ScoreJoueur = ScoreOrdi = 0;
        }
      }

      // faut appuier sur F11 pour le plein ecran
      if (IsKeyPressed(KEY_F11))
      {
        ToggleFullScreenWindow(LargeurEcran, HauteurEcran);
      }
      // faut appuier sur F1 pour pause
      if (IsKeyPressed(KEY_F1))
      {
        EcranActuelle = Pause;
      }

      // pour stopper la musique pendant le jeu
      if (IsKeyPressed(KEY_F4))
        mute = !mute;
      if (mute)
      {
        SetMusicVolume(music, 1.0f);
      }
      else
      {
        SetMusicVolume(music, 0.0f);
      }
    }
    break;

    // ici c'est pour deactiver l'ecran pause
    case Pause:
    {
      if (IsKeyPressed(KEY_F1))
      { // F1 pour quitter la mode pause
        EcranActuelle = Gameplay;
      }

      //  pour enlever la musique
      if (IsKeyPressed(KEY_F4))
        mute = !mute;
      if (mute)
      {
        SetMusicVolume(music, 1.0f);
      }
      else
      {
        SetMusicVolume(music, 0.0f);
      }
    }
    break;

    // toute les choix possible pour la fin de partie
    case fin:
    {
      if (IsKeyPressed(KEY_SPACE))
      { // espace pour rejouer
        EcranActuelle = Gameplay;
      }
      else
      {
        if (IsKeyPressed(KEY_TAB))
        { // TAB pour revenir a l'accueil
          EcranActuelle = Accueil;
        }
      }
    }
    default:
      break;
    }

    // dans cette partie du code c'est pour afficher tout ce qui est graphique
    BeginDrawing();
    switch (EcranActuelle)
    {
    // ici c'est pour afficher les instructions a suivre pour acceder a l'ecran de jeu
    case Accueil:
    {
      ClearBackground(BLACK);
      DrawText("PONG", 120, 20, 120, WHITE);
      DrawText("MEILLEUR PROJET", 120, 140, 60, WHITE);
      DrawText("VOS TOUCHES : Z et S", 120, 390, 20, WHITE);
      DrawText("appuyer sur entrer pour continuer", 120, 450, 20, WHITE);
      DrawText("appuyer sur F4 pour arreter ou reactiver la musique", 120, 510, 20, WHITE);
    }
    break;

    // l'affichage du menu couleur
    case MenuCouleur:
    {
      ClearBackground(BLACK);
      DrawText("PONG", 120, 20, 120, WHITE);
      DrawText("Menu couleur", 120, 140, 60, WHITE);
      DrawText("Pour un jeu classique : B", 300, 300, 40, WHITE);
      DrawText("Pour un jeu remastred bleu : T", 300, 350, 40, WHITE);
      DrawText("Pour un jeu remastred rouge : R", 300, 400, 40, WHITE);
    }
    break;

    // l'affichage du menu de difficulte
    case Niveau:
    {
      ClearBackground(BLACK);
      DrawText("PONG", 120, 20, 120, WHITE);
      DrawText("Menu difficulte", 120, 140, 60, WHITE);
      DrawText("Debutant : D", 300, 300, 40, WHITE);
      DrawText("Itermediaire : I", 300, 350, 40, WHITE);
      DrawText("Expert : E", 300, 400, 40, WHITE);
    }
    break;

    // ici c'est pour l'affichage l'ecran de la partie de jeu
    case Gameplay:
    {
      AfficherPong(Couleur);
    }
    break;

    // l'affichage de l'ecran pause
    case Pause:
    {
      ClearBackground(BLACK);
      DrawText("PAUSE", 350, 225, 120, WHITE);
      DrawText("appuyer sur F1 pour continuer", 200, 410, 30, WHITE);
    }
    break;

    // l'affichage de l'ecran de fin de partie et  les options
    case fin:
    {
      if (gagnant == 2)
      { // ceci est l'ecran de win pour le jouer
        EcranGagnant(Couleur);
      }

      if (gagnant == 1)
      { // ceci est l'ecran de win pour le bot
        EcranLose(Couleur);
      }
    }
    default:
      break;
    }
    EndDrawing();
  }
  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}