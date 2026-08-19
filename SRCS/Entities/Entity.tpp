template<typename T>
void	Entity::runCollisionEvents(const T& others)
{
	setHitboxColor(RED);
	for (auto& e : others)
	{
		if (this == e.get())
			continue ;
		e->setHitboxColor(RED);
		if (collides(*e))
		{
			e->setHitboxColor(GREEN);
			collisionEvent(*e);
			e->collisionEvent(*this);
		}
	}
}
