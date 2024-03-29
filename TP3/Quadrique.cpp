#include "Quadrique.h"

using namespace Scene;

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CQuadrique \n
///  Description : Constructeur par d�faut
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique::CQuadrique( void )
    : ISurface     (                  )
    , m_Quadratique( CVecteur3::ZERO  )
    , m_Lineaire   ( CVecteur3::ZERO  )
    , m_Mixte      ( CVecteur3::ZERO  )
    , m_Cst        ( RENDRE_REEL( 0 ) )
{}

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CQuadrique \n
///  Description : Constructeur par d�faut
///
///  @param [in]       Quadric const Scene::CQuadrique &   la quadrique � copier
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique::CQuadrique( const CQuadrique& Quadric )
    : ISurface     ( Quadric               )
    , m_Quadratique( Quadric.m_Quadratique )
    , m_Lineaire   ( Quadric.m_Lineaire    )
    , m_Mixte      ( Quadric.m_Mixte       )
    , m_Cst        ( Quadric.m_Cst         )
{}

///////////////////////////////////////////////////////////////////////////////
///  public virtual destructor  ~CQuadrique \n
///  Description : Destructeur
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique::~CQuadrique( void )
{
}

///////////////////////////////////////////////////////////////////////////////
///  public  operator = \n
///  Description : Op�rateur de copie
///
///  @param [in]       Quadric const Scene::CQuadrique &    La quadrique � copier
///
///  @return Scene::CQuadrique & La quadrique modifi�e
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique& CQuadrique::operator = ( const CQuadrique& Quadric )
{
    ISurface::operator =( Quadric );
    m_Quadratique = Quadric.m_Quadratique;
    m_Lineaire    = Quadric.m_Lineaire;
    m_Mixte       = Quadric.m_Mixte;
    m_Cst         = Quadric.m_Cst;
    return ( *this );
}

///////////////////////////////////////////////////////////////////////////////
///  protected virtual constant  AfficherInfoDebug \n
///  Description : Impl�mente le d�boguage polymorphique par flux de sortie
///
///  @param [in, out]  Out std::ostream &    Le flux de sortie
///
///  @return std::ostream & Le flux de sortie modifi�
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
ostream& CQuadrique::AfficherInfoDebug( ostream& Out ) const
{
    Out << "[DEBUG]: Quadric.Quadratique       = " << m_Quadratique << endl;
    Out << "[DEBUG]: Quadric.Lineaire          = " << m_Lineaire    << endl;
    Out << "[DEBUG]: Quadric.Mixte             = " << m_Mixte       << endl;
    Out << "[DEBUG]: Quadric.Constante         = " << m_Cst;
    return Out;
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual  Pretraitement \n
///  Description : Pretraitement des donn�es de la quadrique( appel� AVANT le lancer)
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
void CQuadrique::Pretraitement( void )
{
   // Algorithme tir� de ... 
   // R. Goldman, "Two Approach to a Computer Model for Quadric Surfaces",
   // IEEE CG&A, Sept 1983, pp.21
   
    REAL A = m_Quadratique.x;
	REAL B = m_Quadratique.y;
    REAL C = m_Quadratique.z;
    REAL D = m_Mixte.z    * RENDRE_REEL( 0.5 );
	REAL E = m_Mixte.x    * RENDRE_REEL( 0.5 );
	REAL F = m_Mixte.y    * RENDRE_REEL( 0.5 );
	REAL G = m_Lineaire.x * RENDRE_REEL( 0.5 );
	REAL H = m_Lineaire.y * RENDRE_REEL( 0.5 );
	REAL J = m_Lineaire.z * RENDRE_REEL( 0.5 );
	REAL K = m_Cst;

	CMatrice4 Q( A, D, F, G,
			     D, B, E, H,
			     F, E, C, J,
			     G, H, J, K );

    CMatrice4 Inverse = m_Transformation.Inverse();

    Q = Inverse * Q * Inverse.Transpose();

    m_Quadratique.x = Q[ 0 ][ 0 ];
    m_Quadratique.y = Q[ 1 ][ 1 ];
	m_Quadratique.z = Q[ 2 ][ 2 ];
	m_Cst           = Q[ 3 ][ 3 ];
	m_Mixte.x       = Q[ 1 ][ 2 ] * RENDRE_REEL( 2.0 );
	m_Mixte.y       = Q[ 0 ][ 2 ] * RENDRE_REEL( 2.0 );
	m_Mixte.z       = Q[ 0 ][ 1 ] * RENDRE_REEL( 2.0 );
	m_Lineaire.x    = Q[ 0 ][ 3 ] * RENDRE_REEL( 2.0 );
	m_Lineaire.y    = Q[ 1 ][ 3 ] * RENDRE_REEL( 2.0 );
    m_Lineaire.z    = Q[ 2 ][ 3 ] * RENDRE_REEL( 2.0 );
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual  Intersection \n
///  Description : Effectue l'intersection Rayon/Quadrique
///
///  @param [in]       Rayon const CRayon &    Le rayon � tester
///
///  @return Scene::CIntersection Le r�sultat de l'ntersection
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CIntersection CQuadrique::Intersection( const CRayon& Rayon )
{
	CIntersection Result;

	// TODO: � COMPL�TER ...

	// La r�f�rence pour l'algorithme d'intersection des quadriques est : 
	// Eric Haines, Paul Heckbert "An Introduction to Rayon Tracing",
	// Academic Press, Edited by Andrw S. Glassner, pp.68-73 & 288-293
	
	//Il existe X,Y,Z,t tels que : ??
	//Rayon.ObtenirOrigine().x + t * Rayon.ObtenirDirection().x == X * CMatrice4 Q( A, D, F, G,
	//															   Y			    D, B, E, H,
	//															   Z			    F, E, C, J,      * (X,Y,Z,1)
	//															   1				G, H, J, K )

	REAL A = m_Quadratique.x;
	REAL B = m_Quadratique.y;
	REAL C = m_Quadratique.z;
	REAL D = m_Mixte.z;
	REAL E = m_Mixte.x;
	REAL F = m_Mixte.y;
	REAL G = m_Lineaire.x;
	REAL H = m_Lineaire.y;
	REAL J = m_Lineaire.z;
	REAL K = m_Cst;
	REAL xo = Rayon.ObtenirOrigine().x;
	REAL yo = Rayon.ObtenirOrigine().y;
	REAL zo = Rayon.ObtenirOrigine().z;
	REAL xd = Rayon.ObtenirDirection().x;
	REAL yd = Rayon.ObtenirDirection().y;
	REAL zd = Rayon.ObtenirDirection().z;
	bool intersection = false;
	REAL t = 0;

	REAL Aq = A*xd*xd + B*yd*yd + C*zd*zd + D*xd*yd + E*xd*zd + F*yd*zd;
	REAL Bq = 2 * A*xo*xd + 2 * B*yo*yd + 2 * C*zo*zd + D*(xo*yd + yo*xd) + E*(xo*zd + zo*xd) + F*(yo*zd + yd*zo) + G*xd + H*yd + J*zd;
	REAL Cq = A*xo*xo + B*yo*yo + C*zo*zo + D*xo*yo + E*xo*zo + F*yo*zo + G*xo + H*yo + J*zo + K;
	if (Aq == 0) {
		t = -Cq / Bq;
		intersection = true;
	} else {
		REAL delta = Bq * Bq - 4 * Aq * Cq;
		if (delta > EPSILON) {
			t = (-Bq - sqrt(delta)) / (2 * Aq);
			if (t < EPSILON) {
				t = (-Bq + sqrt(delta)) / (2 * Aq);
				intersection = true;
			}
			else
			{
				intersection = true;
			}
		}
	}

	if (intersection) {
		CVecteur3 pos = CVecteur3(xo + t*xd, yo + t*yd, zo + t*zd);
		CVecteur3 normale = CVecteur3::Normaliser(CVecteur3(2 * A*pos.x + D*pos.y + E*pos.z + G,
			2 * B*pos.y + D*pos.x + F*pos.z + H,
			2 * C*pos.z + E*pos.x + F*pos.y + J));

		// S'il y a collision, ajuster les variables suivantes de la structure intersection :
		// Normale, Surface intersect�e et la distance
		Result.AjusterNormale(normale);
		Result.AjusterSurface(Copier());
		Result.AjusterDistance(t);
	}
	return Result;
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual constant  Copier \n
///  Description : Alloue une copie de la quadrique courante
///
///  @return Scene::CQuadrique *la copie de la quadrique
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique* CQuadrique::Copier( void ) const
{
    return new CQuadrique( *this );
}